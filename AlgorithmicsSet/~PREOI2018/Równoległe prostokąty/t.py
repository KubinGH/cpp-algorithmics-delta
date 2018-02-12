import os, random
import itertools

INSTANT_RUN = False
FORCE_FILENAME = None
SELF_TEST = False
SAFE_TEST = False

test_filename_pattern = "tests/testf{i}.{ext}"
n = 10**5
bounds = (-170, 170)
test_iterable = range(10)

def randpoints(n=n, bounds=bounds, safe=SAFE_TEST):
    if SAFE_TEST:
        if (bounds[1] - bounds[0] + 1)**2 <= n:
            raise ValueError("Can't assign this amount of unique points")
        result = []
        result_set = set()
        while len(result) < n:
            current = (random.randint(*bounds), random.randint(*bounds))
            if current not in result_set:
                result.append(current)
                result_set.add(current)
        return result
    else:
        return [(random.randint(*bounds), random.randint(*bounds)) for _ in range(n)]

for i in test_iterable:
    print("Generating  test")
    points = randpoints()#[(int(p.split(" ")[0]), int(p.split(" ")[1])) for p in IN.split("\n")]
    result = None
    if SELF_TEST:
        result = 0
        print("Test self")
        R = set()
        for pi, p1 in enumerate(points):
            x1, y1 = p1
            for p2 in points[pi+1:]:
                x2, y2 = p2
                try:
                    t = tuple(sorted((points.index((x1, y1)), points.index((x2, y1)), 
                                      points.index((x2, y2)), points.index((x1, y2)))))
                except ValueError:
                    continue
                if (abs(x2-x1)*abs(y2-y1) > 0) and t not in R:
                    R.add(t)
                    result += 1
    if len(points) < 500: print(points, "->", result)
    print("Save file")
    if not FORCE_FILENAME:
        test_filename = test_filename_pattern
    else:
        test_filename = FORCE_FILENAME
    with open(test_filename.format(i=i, ext="in"), "w") as file:
        file.write("{}\n".format(n))
        for x, y in points:
            file.write("{} {}\n".format(x, y))
    with open(test_filename.format(i=i, ext="out"), "w") as file:
        file.write(str(result))
    if INSTANT_RUN and SELF_TEST:
        print("Test run")
        if SELF_TEST:
            os.system("thetacheck -a prostokaty.exe -o {} > tmp.thetacheck.out".format(test_filename.format(i=i, ext="")[:-1]))
            if not open("tmp.thetacheck.out", "r").read().strip().endswith("(100.0%)"):
                break
        else:
            os.system("prostokaty.exe < {}".format(test_filename))
