#include <stdio.h>
#include <string.h>
#include <assert.h>

#define REACHED_END 1
#define INVALID 0
#define MAX_TAG_NAME_LEN 20

char html_verifier(const char *html);

int main()
{
    assert(1 == html_verifier("<html><head><title/></head></html>"));
    assert(0 == html_verifier("<html><head><title/></head>"));
    assert(0 == html_verifier("<html><body></html>"));
    assert(0 == html_verifier("<html><body><p>"));
    assert(0 == html_verifier("<html><body/><p>"));
    assert(1 == html_verifier("<html><body><p><title/></p></body></html>"));

    puts("OK!");
    return 0;
}

#define MAX_TAG_LEN 20
char html_verifier_rec(char ** html) {
	if(**html == '\0') {
		return 0;
	}
	char aux[MAX_TAG_LEN + 1] = {0};
	
	// me salteo el <
	(*html)++;

	char * tag = *html;

	int dim;
	int reached_end = 0;
	for(dim = 0; tag[dim] != '>'; dim++) {
		if(tag[dim] == '/') {
			reached_end = 1;
		} else {
			aux[dim] = tag[dim];
		}
	}

	// saltear el tag, y el > 
	*html += dim+1;

	if(reached_end) {
		return 1;
	}

	int ret_value = html_verifier_rec(html);

	if(ret_value == 0 || **html == '\0') {
		return 0;
	}

	// salteo </
	*html += 2;

	// comparo con el tag guardado
	if(strncmp(aux, *html, dim) != 0) {
		return 0;
	}

	// salteo el tag, y el >
	*html += dim+1;

	return 1;
}


char html_verifier(const char *html) {
	return html_verifier_rec((char **)&html);
}

