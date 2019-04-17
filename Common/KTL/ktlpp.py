import argparse
import abc
import os
import re

ktl_path = os.environ["KTLPATH"]

ktl_include_begin_tag = "#pragma once"
ktl_include_internal = r"#include \".*?\""

def ktl_include_match(line, verbose=False):
    return line.split()[0] == "include"

def ktl_include_apply(line, tag=ktl_include_begin_tag, verbose=False):
    if verbose: print("[ktl_include] Parsing include '{}'".format(line))
    name = line.split()[1]
    name = name.strip('"')
    content = open(ktl_path + "/" + name, "r").read().split("\n")
    if tag in content:
        i = content.index(tag)
        content = content[i+1:]
    content1 = []
    for line in content:
        if re.match(ktl_include_internal, line):
            if verbose: print("[ktl_include] * Internal include required: '{}'".format(line))
        else:
            content1.append(line)
    return content

class Rule:
    def __init__(self, match, apply):
        self.match, self.apply = match, apply

class KTLPreprocessor:
    default_call_line = "#pragma KTL "
    default_ruleset = {
        "include": Rule(ktl_include_match, ktl_include_apply)
    }
    def __init__(self, verbose, ruleset=default_ruleset, call_line=default_call_line):
        self.verbose = verbose
        self.ruleset = ruleset
        self.call_line = call_line

    def apply(self, code):
        if self.verbose: print("[main]: Running preprocessor...")
        output = []
        for line in code.split("\n"):
            if line.startswith(self.call_line):
                sline = line[len(self.call_line):]
                for name, rule in self.ruleset.items():
                    if rule.match(sline, verbose=self.verbose):
                        output.extend(rule.apply(sline, verbose=self.verbose))
            else:
                output.append(line)
        if self.verbose: print("[main]: Done.")
        return "\n".join(output)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog="ktlpp", description="The KTL Preprocessor")

    parser.add_argument("inputfile", help="Input file")
    parser.add_argument("outputfile", help="Output file")

    parser.add_argument("-v", "--verbose", action="store_true")

    args = parser.parse_args()

    content = open(args.inputfile, "r").read()
    pp = KTLPreprocessor(
        verbose=args.verbose
    )
    output = pp.apply(content)

    with open(args.outputfile, "w") as out:
        out.write(output)