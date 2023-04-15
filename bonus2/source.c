int language = 0;

void greetuser(char* name) {
	char* buffer[???]; // TODO

	if (lang == 1) {
		strcpy(buffer, "Hyvää päivää ");
	} else if (lang == 2) {
		strcpy(buffer, "Goedemiddag! ");
	} else if (lang == 0) {
		strcpy(buffer, "Hello ");
	}

	strcat(buffer, name);
	puts(buffer);
}

int main(int argc, char** argv) {
	char buffer[72]; // точно ли 72

	if (argc != 3) {
		return 1
	}

	memset(buffer, 0, 72);
	strncpy(buffer, argv[1], 40);
	strncpy(&buffer[40], argv[2], 32);
	char* env = getenv("LANG");

	if (env != 0) {
		if (memcmp(env, "fi", 2) == 0) { 
			language = 1 
		} else if (memcmp(env, "nl", 2) == 0) {
			language = 2 
		}
	}

	greetuser(buffer);
	return 0;
}