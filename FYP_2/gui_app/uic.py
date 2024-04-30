import os
import glob
import subprocess

os.makedirs('src/auto_gen', exist_ok=True)

for root, dirs, files in os.walk('src'):
    for file in files:
        if file.endswith('.ui'):
            file_path = os.path.join(root, file)
            file_name = os.path.splitext(file)[0]
            output_file = os.path.join('src/auto_gen', 'ui_' + file_name + '.h')

            print(f'uic {file}')
            subprocess.run(['third_party/qt/bin/uic.exe', '-o', output_file, file_path], check=True)
