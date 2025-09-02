/* This test is from Git's t/helper/test-wildmatch.c */

#include <stdio.h>
#include <stdlib.h>
//#include <string>
#include <string.h>

//#include <cstdio>

#include <wildmatch/wildmatch.h>

void die(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

char *make_str(const char *s)
{
	const size_t size = strlen(s);
	char *result = malloc(size * 2);
	size_t out_size = 0;
	for (size_t i = 0; i < size; ++i)
	{
		char c = s[i];
		if (c == '\\')
		{
			result[out_size++] = '\\';
		}
		result[out_size++] = c;
	}
	result[out_size] = 0;
	return result;
}

int main(int argc, char **argv)
{


	//int r_cs = wildmatch("**[!te]", "ten", WM_WILDSTAR);
	//printf("**[!te]' 'ten' check, CS:%d\n", r_cs);
	//int r_ci = wildmatch("**[!te]", "ten", WM_WILDSTAR | WM_CASEFOLD);
	//printf("**[!te]' 'ten' check, CI:%d\n", r_ci);

    int i;
    if (argc < 4) {
        die("usage: test-wildmatch <mode> <string> <pattern>\n"
            "modes: wildmatch, iwildmatch, pathmatch");
    }
    for (i = 2; i < argc; i++) {
        if (argv[i][0] == '/')
            die("Forward slash is not allowed at the beginning of the\n"
                "pattern because Windows does not like it. Use `XXX/' instead.");
        else if (!strncmp(argv[i], "XXX/", 4))
            argv[i] += 3;
    }
	FILE *f = fopen("/home/victor/Downloads/wildmatch-main_davvid/wildmatch-main/log.log", "a");
	int result = 0;
	int case_sensitive = 1;
    if (!strcmp(argv[1], "wildmatch"))
	{
        result = !!wildmatch(argv[3], argv[2], WM_WILDSTAR);
	}
    else if (!strcmp(argv[1], "iwildmatch"))
	{
		case_sensitive = 0;
        result = !!wildmatch(argv[3], argv[2], WM_WILDSTAR | WM_CASEFOLD);
	}
    else if (!strcmp(argv[1], "pathmatch"))
	{
        result = !!wildmatch(argv[3], argv[2], 0);
		fprintf(f, "skipped pathmatch\n");
		fclose(f);
		return result;
	}
    else
	{
		fprintf(f, "Unexpected\n");
		fclose(f);
        return 1;
	}

	char *text = make_str(argv[2]);
	char *pattern = make_str(argv[3]);

	fprintf(f, "\t{\"%s\", \"%s\", %s, %s},\n",
			text,
			pattern,
			result ? "false" : "true",
			case_sensitive ? "MatchCase::CaseSensitive" : "MatchCase::CaseInsensitive");
	fclose(f);
	free(text);
	free(pattern);
	return result;
}
