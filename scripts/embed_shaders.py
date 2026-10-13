import sys
from pathlib import Path

*shader_sources,output = sys.argv[1:]
output_path = Path(output)

header: list[str] = []

header.append("#pragma once\n")
header.append("namespace shaders{\n")


for shader in shader_sources:
    variable_name = shader.removeprefix("shaders/").replace('.','_')

    content = ""
    with open(shader,"r") as file:
        content = file.read()
    header.append(f"""const char*const {variable_name} = R\"SHADER(\n{content})SHADER\";\n""")

header.append("}")
final = "\n".join(header)

with open(output,"w") as file:
    file.write(final)