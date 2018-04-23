import subprocess
import random

def main(command="kafelki-min.exe", verbose=True):
    def call_with_io(command, string=""):
        bytes_input = string.encode("utf-8")
        process = subprocess.run(command, shell=True, input=bytes_input, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
        result = process.stdout.decode("utf-8", errors="replace").replace("\r\n", "\n")
        return result

    for p in range(1, 51):
        if p >= 50: p = 250
        for _ in range(5):
            i = random.randint(1, 10**min(p, 250))
            x = call_with_io(command, str(i)).strip()
            if verbose:
                print(f"3*{i} + 8 = {x}")
            if x != str(3 * i + 8):
                print(f"!@#: ->{x} != +{3*i+8}")
                return False
    return True