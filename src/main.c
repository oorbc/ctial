#include<stdio.h>
#include<string.h>
#include"error.h"
#include"utils.h"
#include"actions.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		pr_usage();
		return 1;
	}

	Input input;
	int act_set = 0;
	int tar_set = 0;
	int arg_set = 0;

	// parsing input
	for (int i = 1; i < argc; ++i) {
		// get action
		// insert
		if (strcmp(argv[i], "-i") == 0) {
			check_conflict(ActionConflict, act_set, i);
			input.action = Insert;
			++act_set;
		}
		// delete
		else if (strcmp(argv[i], "-d") == 0) {
			check_conflict(ActionConflict, act_set, i);
			input.action = Delete;
			++act_set;
		}
		// modify
		else if (strcmp(argv[i], "-m") == 0) {
			check_conflict(ActionConflict, act_set, i);
			input.action = Modify;
			++act_set;
		}

		// get target
		else if (strcmp(argv[i], "-t") == 0) {
			check_conflict(TargetConflict, tar_set, i);
			++tar_set;
			if (i == argc - 1) {
				pr_err_arg(TargetMissingEx, i);
				return 1;
			}

			if (argv[i + 1][0] == '-') {
				pr_err_arg(TargetMissingEx, i);
				return 1;
			}
		
			strcpy(input.target, argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "-m") == 0) {
			check_conflict(ArgConflict, arg_set, i);
			++arg_set;
			if (i == argc - 1) {
				pr_err_arg(ArgMissingEx, i);
				return 1;
			}

			if (argv[i + 1][0] == '-') {
				pr_err_arg(ArgMissingEx, i);
				return 1;
			}

			strcpy(input.arg, argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "-l") == 0) {
			check_conflict(ArgConflict, arg_set, i);
			input.action = List;
			++act_set;
		}
		else if (strcmp(argv[i], "-h") == 0) {
			pr_help();
			return 1;
		}
		else if (strcmp(argv[i], "--setup") == 0) {
			setup();
			return 1;
		}
		else if (strcmp(argv[i], "-passwd") == 0) {
			// todo change_passwd();
			return 1;
		}
		else {
			printf("Unrecognized argument '%s'\n", argv[i]);
			return 1;
		}
	}

	switch (input.action) {
		case Insert:
			insert(input);
			break;
	}

	return 0;
}
