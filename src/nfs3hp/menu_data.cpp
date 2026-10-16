#include <lib/file.h>
#include <SDL3/SDL.h>
#include <cctype>
#include <cstddef>
#include <string>
#include <vector>

/* The port's versions of the game's menu files, handed to the game in place of
 * the imported ones (win32::File::setReadSubstitute); the imported data stays
 * as it was.
 *
 * MENUS/MAINSPLT.MNU, the main menu for two players on one machine, as the
 * CD has it, lacks two things MAIN.MNU and later copies of the file have:
 * - the makers' names drifting behind the items, MAIN.MNU's image `nfsl`
 *   (codelink texteffects) -- the same [image] put in after `mask`, where the
 *   later copies have it;
 * - car and opponent lists nine lines long (maxvisitem=9), not seven and five.
 * The rows the items stand in are moved up as the screen opens
 * (native_frontend_main.cpp, onSplitEnter), so the longer lists fit.
 *
 * MENUS/SETUP.MNU, the first screen: its "NFS Web Site" button opens Options
 * instead, the way the race screen's Options button does (nextmenu=options,
 * MAIN.MNU's text for it).  Its codelink goes too, or the screen's code
 * (sub_452f80) would find it by SETUP_NfsWebSite and make it open the web
 * site again; the code passes over a button it does not find. */

namespace nfs3hp
{

namespace
{

bool endsWith(const std::string& text, const char* suffix)
{
    const std::string tail(suffix);
    if (text.size() < tail.size())
        return false;
    for (size_t i = 0; i < tail.size(); ++i)
        if (std::tolower(static_cast<unsigned char>(text[text.size() - tail.size() + i])) != tail[i])
            return false;
    return true;
}

std::string lower(std::string text)
{
    for (char& c : text)
        c = char(std::tolower(static_cast<unsigned char>(c)));
    return text;
}

bool readWhole(const std::string& path, std::string& out)
{
    size_t size = 0;
    void* data = SDL_LoadFile(path.c_str(), &size);
    if (!data)
        return false;
    out.assign(static_cast<const char*>(data), size);
    SDL_free(data);
    return true;
}

/* The CD's MAINSPLT.MNU with the two changes; empty when it has them already
 * or is not laid out as expected. */
std::string fixSplitMenu(const std::string& original)
{
    if (lower(original).find("image=nfsl") != std::string::npos)
        return std::string();
    const std::string eol = original.find("\r\n") != std::string::npos ? "\r\n" : "\n";

    std::vector<std::string> lines;
    for (size_t at = 0; at <= original.size();)
    {
        size_t end = original.find('\n', at);
        if (end == std::string::npos)
            end = original.size();
        std::string line = original.substr(at, end - at);
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        lines.push_back(line);
        at = end + 1;
    }

    // Sections: where each starts, and the lists' and the mask's.
    std::vector<std::string> out;
    bool afterMask = false, logoIn = false;
    std::string sectionList;
    std::vector<size_t> maxVisible;  // the lines of the section now open
    auto closeSection = [&]() {
        if (sectionList == "cars" || sectionList == "car2" || sectionList == "opcars")
            for (size_t line : maxVisible)
                out[line] = "maxvisitem=9";
        sectionList.clear();
        maxVisible.clear();
    };
    for (const std::string& line : lines)
    {
        const std::string key = lower(line);
        if (!key.empty() && key[0] == '[')
        {
            closeSection();
            if (afterMask && !logoIn)
            {
                for (const char* logo : { "[image]", "x=236", "y=118", "priority=6", "codelink=texteffects",
                                          "image=nfsl", "fadelevel=0", "" })
                    out.push_back(logo);
                logoIn = true;
            }
        }
        else if (key == "image=mask")
            afterMask = true;
        else if (key.rfind("listname=", 0) == 0)
            sectionList = key.substr(9);
        else if (key.rfind("maxvisitem=", 0) == 0)
            maxVisible.push_back(out.size());
        out.push_back(line);
    }
    closeSection();
    if (!logoIn)
        return std::string();

    std::string fixed;
    for (size_t i = 0; i < out.size(); ++i)
    {
        fixed += out[i];
        if (i + 1 < out.size())
            fixed += eol;
    }
    return fixed;
}

/* The CD's SETUP.MNU with the web site button turned into Options; empty when
 * it has no such button. */
std::string fixSetupMenu(const std::string& original)
{
    const std::string eol = original.find("\r\n") != std::string::npos ? "\r\n" : "\n";
    std::vector<std::string> lines;
    for (size_t at = 0; at <= original.size();)
    {
        size_t end = original.find('\n', at);
        if (end == std::string::npos)
            end = original.size();
        std::string line = original.substr(at, end - at);
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        lines.push_back(line);
        at = end + 1;
    }

    // The section the button is in: from the [button] before its codelink to
    // the next section.
    size_t codelink = lines.size();
    for (size_t i = 0; i < lines.size(); ++i)
        if (lower(lines[i]) == "codelink=setup_nfswebsite")
            codelink = i;
    if (codelink == lines.size())
        return std::string();
    size_t end = codelink + 1;
    while (end < lines.size() && (lines[end].empty() || lines[end][0] != '['))
        ++end;
    lines[codelink] = "codelink=SETUP_OPTIONS";
    bool text = false;
    for (size_t i = codelink + 1; i < end; ++i)
    {
        if (lower(lines[i]).rfind("text=", 0) == 0)
        {
            lines[i] = "text=kMenuMAINOptions001";
            lines.insert(lines.begin() + std::ptrdiff_t(i) + 1, "nextmenu=options");
            text = true;
            break;
        }
    }
    if (!text)
        return std::string();

    std::string fixed;
    for (size_t i = 0; i < lines.size(); ++i)
    {
        fixed += lines[i];
        if (i + 1 < lines.size())
            fixed += eol;
    }
    return fixed;
}

std::string cacheDirectory()
{
#ifdef __ANDROID__
    const char* cache = SDL_GetAndroidCachePath();
    return cache ? std::string(cache) + "/" : std::string();
#else
    char* pref = SDL_GetPrefPath("nfs3hp", "port");
    std::string path = pref ? pref : "";
    SDL_free(pref);
    return path;
#endif
}

/* The port's version of the menu file at `path`, made once a run by `fix` from
 * the file the game would have read and kept as `name` in the cache; empty
 * when there is none, and the game reads its own. */
struct MadeMenu
{
    std::string made;
    bool tried = false;
};

std::string portMenu(const std::string& path, const char* name, std::string (*fix)(const std::string&),
                     MadeMenu& state)
{
    if (state.tried)
        return state.made;
    state.tried = true;
    std::string original;
    if (!readWhole(path, original))
        return state.made;
    const std::string fixed = fix(original);
    const std::string directory = cacheDirectory();
    if (fixed.empty() || directory.empty())
        return state.made;
    const std::string copy = directory + lower(name);
    if (!SDL_SaveFile(copy.c_str(), fixed.data(), fixed.size()))
    {
        SDL_Log("[FE] %s: cannot write %s: %s", name, copy.c_str(), SDL_GetError());
        return state.made;
    }
    SDL_Log("[FE] %s: the port's version, %s", name, copy.c_str());
    state.made = copy;
    return state.made;
}

std::string menuData(const std::string& path)
{
    static MadeMenu split, setup;
    if (endsWith(path, "/fedata/menus/mainsplt.mnu"))
        return portMenu(path, "MAINSPLT.MNU", fixSplitMenu, split);
    if (endsWith(path, "/fedata/menus/setup.mnu"))
        return portMenu(path, "SETUP.MNU", fixSetupMenu, setup);
    return std::string();
}

}

void installMenuData()
{
    win32::File::setReadSubstitute(menuData);
}

}
