#include <stdio.h>

#define DIR "images/bonus"

int main() {
	printf("Opening dir: %s\n", DIR);
	FILE *f = fopen(DIR, "rb");

	return 0;
}
