import os
import glob
import subprocess

os.makedirs('src/auto_gen', exist_ok=True)

for root, dirs, files in os.walk('src'):
    for file in files:
        if file.endswith('.h'):
            file_path = os.path.join(root, file)

            with open(file_path, 'r') as f:
                if 'Q_OBJECT' in f.read():
                    file_name = os.path.splitext(file)[0]
                    output_file = os.path.join('src/auto_gen', file_name + '_auto_gen.cpp')

                    print(f'moc {file}')
                    subprocess.run(['third_party/qt/bin/moc.exe', '-o', output_file, file_path], check=True)