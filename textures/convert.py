import os
import json

# write a simple data file with frames in first and in second sprite with associated frame
def write_parse_sprite(data, output_file):
	with open(output_file, 'w') as file:
		file.write(f"frames {len(data['frames']) + len(data['meta']['slices'])}\n")
		for frame in data['frames']:
			file.write(f"{frame['frame']['x']} {frame['frame']['y']} {frame['frame']['w']} {frame['frame']['h']}\n")
		for tags in data['meta']['slices']:
			file.write(f"{tags['keys'][0]["bounds"]['x']} {tags['keys'][0]["bounds"]['y']} {tags['keys'][0]["bounds"]['w']} {tags['keys'][0]["bounds"]['h']}\n")
		file.write(f"slices {len(data['meta']['frameTags']) + len(data['meta']['slices'])}\n")
		for tags in data['meta']['frameTags']:
			file.write(f"{tags['name']} {tags['from']} {tags['to']}\n")
		i = 0
		for tags in data['meta']['slices']:
			file.write(f"{tags['name']} {len(data['frames']) + i}\n")
			i += 1

def parse_json_files(directory):
	for filename in os.listdir(directory):
		if filename.endswith(".json"):
			filepath = os.path.join(directory, filename)
			with open(filepath, 'r') as file:
				try:
					data = json.load(file)
					write_parse_sprite(data, f"{filename}.data")
				except json.JSONDecodeError as e:
					print(f"Error parsing {filename}: {e}")

if __name__ == "__main__":
	current_directory = os.path.dirname(os.path.abspath(__file__))
	parse_json_files(current_directory)