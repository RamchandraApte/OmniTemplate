with open("../docs/html/index.qhp", "r+") as qhp:
    lines = qhp.readlines()
    lines.insert(-3, "<file>m-light+documentation.compiled.css</file>")
    qhp.seek(0)
    qhp.truncate()
    qhp.writelines(lines)
