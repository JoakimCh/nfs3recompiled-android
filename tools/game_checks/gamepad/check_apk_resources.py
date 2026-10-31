#!/usr/bin/env python3
"""Verify actual packaged app R fields against APK resources and app-owned symbols.
Usage: check_apk_resources.py APK BUILD_TOOLS APP_COMPILE_R_TXT REPORT_JSON
Catches stale runtime R dex even when Java compilation/resources separately pass.
"""
from pathlib import Path
import os,re,sys,json,zipfile,tempfile,subprocess
apk,bt,symbols,report=map(Path,sys.argv[1:]);report.parent.mkdir(parents=True,exist_ok=True)
env=os.environ.copy();env['LD_LIBRARY_PATH']=str(bt/'lib64')+':'+env.get('LD_LIBRARY_PATH','')
resources=subprocess.check_output([str(bt/'aapt2'),'dump','resources',str(apk)],env=env).decode('utf-8','replace')
ids={(kind,name):int(value,16) for value,kind,name in re.findall(r'resource (0x[0-9a-fA-F]+) ([\w]+)/([\w]+)',resources)}
required=[]
for line in symbols.read_text().splitlines():
 parts=line.split()
 if len(parts)==4 and parts[0]=='int' and parts[1]!='styleable':required.append((parts[1],parts[2]))
fields={};duplicates=[]
with tempfile.TemporaryDirectory(prefix='apk-resource-check-',dir=report.parent) as tmp:
 with zipfile.ZipFile(apk) as z:
  for name in z.namelist():
   if not re.fullmatch(r'classes\d*\.dex',name):continue
   path=Path(tmp)/name;path.write_bytes(z.read(name))
   dump=subprocess.check_output([str(bt/'dexdump'),'-f',str(path)],env=env).decode('utf-8','replace')
   for match in re.finditer(r"Class descriptor\s*: 'Ldev/nfs3hp/port/R\$(\w+);'",dump):
    kind=match.group(1);end=dump.find('\nClass #',match.end());block=dump[match.end():end if end>=0 else None]
    if 'Static fields' not in block:continue
    block=block.split('Static fields',1)[1].split('Instance fields',1)[0]
    field=type_=None
    for line in block.splitlines():
     m=re.search(r"name\s*: '([^']+)'",line)
     if m:field=m.group(1);type_=None
     m=re.search(r"type\s*: '([^']+)'",line)
     if m:type_=m.group(1)
     m=re.search(r'value\s*: (-?\d+)',line)
     if m and field and type_=='I':
      key=(kind,field)
      if key in fields:duplicates.append('/'.join(key))
      fields[key]=int(m.group(1))&0xffffffff
mismatches=[]
for key in required:
 expected=ids.get(key);actual=fields.get(key)
 if expected is None or actual!=expected:mismatches.append({'resource':'/'.join(key),'apk_id':None if expected is None else hex(expected),'packaged_R_id':None if actual is None else hex(actual)})
result={'apk':apk.name,'app_resources_checked':len(required),'packaged_app_int_fields':len(fields),'mismatches':mismatches,'duplicate_fields':duplicates,'passed':not mismatches and not duplicates}
report.write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps(result,indent=2))
raise SystemExit(0 if result['passed'] else 1)
