import glob
def fix(fname):
    with open(fname, "r+") as fp:
        code = fp.read()
        print(fname, code)
        try:
            if not code.splitlines()[1].startswith('#include "core.hpp"'):
                lines = code.splitlines()
                lines.insert(1, '#include "core.hpp"')
                print(lines)
                fp.seek(0)
                fp.write("\n".join(lines))
                fp.truncate()
        except:
            pass
for fname in glob.glob("*.hpp"):
    fix(fname)
