import os
import sys

def file_to_cpp_vector(file_path, variable_name="bytes", array_type="byte_vec"):
    if not os.path.isfile(file_path):
        print(f"File not found: {file_path}")
        return

    with open(file_path, 'rb') as f:
        data = f.read()

    vector_init = f"{array_type} {variable_name} = {{\n    "

    hex_values = [f'0x{byte:02x}' for byte in data]
    hex_lines = [", ".join(hex_values[i:i+16]) for i in range(0, len(hex_values), 16)]

    vector_init += ",\n    ".join(hex_lines)
    vector_init += "\n};"

    print(vector_init)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python file_to_cpp_vector.py <file_path> [variable_name] [array_type]")
        sys.exit(1)

    file_path = sys.argv[1]
    variable_name = sys.argv[2] if len(sys.argv) > 2 else "bytes"
    array_type = sys.argv[3] if len(sys.argv) > 3 else "byte_vec"

    file_to_cpp_vector(file_path, variable_name, array_type)

