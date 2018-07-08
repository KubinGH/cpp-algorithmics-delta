from gamma import call_with_io

brute = "brakuje.exe"
model = "brakuje-beta.exe"

S = "921"

for n in range(1, 10**5+1):
    brute_result = call_with_io(brute, f"{S} {n}")
    model_result = call_with_io(model, f"{S} {n}")
    print(n, "->", brute_result, model_result)
    assert brute_result == model_result