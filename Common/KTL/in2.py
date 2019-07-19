# in2 - C++ Include Inliner

import os
import re
import sys
import argparse
from pathlib import Path

ii_begin_mark = "\n// -*- {name} -*-\n\n"
ii_end_mark = "\n\n// -$- {name} -$-\n"
internal_include_pattern = '#include "(.*?)"'
include_read_mark = "#pragma once"

def frame_include(name, text):
    if include_read_mark in text:
        i = text.find(include_read_mark)
        text = text[i+len(include_read_mark):]
    text = text.strip()
    return ii_begin_mark.format(name=name) + text + ii_end_mark.format(name=name)

def resolve_include(include, ipaths):
    for ipath in ipaths:
        candidate = ipath / include
        if candidate.is_file():
            return candidate.resolve()
    else:
        print(f"[!] '{include}' was not resolved, but it matched the include pattern")
        return None

def resolve_internal(filename, included, ipaths, level=0, encoding=None):
    pref = " "*level
    if filename in included:
        print(pref + f"-# {filename}")
        return ""
    print(pref + f"-> {filename}")

    filepath = resolve_include(filename, ipaths)
    print(pref + f"..resolved to {filepath}")
    with filepath.open(encoding=encoding) as f:
        content = f.read()

    out = ""
    for sub in re.findall(internal_include_pattern, content):
        subpath = Path(sub)
        resub = (Path(filename).parents[0] / subpath).resolve().relative_to(Path.cwd())
        out += resolve_internal(str(resub), included, ipaths, level+1, encoding)
    content = re.sub(internal_include_pattern + "\n", "", content)
    out += frame_include(filename, content)

    included.append(filename)
    return out


if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog="in2", description="Include Inliner")

    parser.add_argument("infile", help="Input file")
    parser.add_argument("outfile", help="Output file")
    parser.add_argument("pattern", help="Regular expression matching includes to inline. Group 0 should yield the filename.")

    parser.add_argument("-e", "--encoding", default=None, help="Encoding to open and save files in")
    parser.add_argument("-p", "--ipaths", help="Path to look for includes in", nargs="*")
    parser.add_argument("-n", "--nointernal", action="store_true", help="Disrespect internal includes (enclosed in \"\")")

    args = parser.parse_args()

    infile = Path(args.infile)
    outfile = Path(args.outfile)

    with infile.open(encoding=args.encoding) as f:
        content = f.read()

    include_pattern = f"({args.pattern})"
    ipaths = [Path(ipath).expanduser() for ipath in args.ipaths]

    print(re.findall(include_pattern, content))

    replacements = {}
    include_files = []

    for full, filename in re.findall(include_pattern, content):
        print(f"Found include: '{full}', leading to file '{filename}'")
        res = resolve_include(filename, ipaths)
        if res is not None:
            if args.nointernal:
                print(f"-> {res}")
                with res.open(encoding=args.encoding) as f:
                    replacements[full] = frame_include(filename, f.read())
            else:
                replacements[full] = resolve_internal(filename, include_files, ipaths, encoding=args.encoding)
            include_files.append(filename)

    recontent = content
    for a, b in replacements.items():
        recontent = recontent.replace(a, b)
    recontent = recontent.strip() + "\n"

    with outfile.open("w", encoding=args.encoding) as f:
        f.write(recontent)

    print("Done!")
