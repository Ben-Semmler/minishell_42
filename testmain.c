#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int	main()
{
	printf("hello this is a test program\n");

	fprintf(stderr, "HERE IS AN ERROR FOR YOU\n");
	exit(69);
}
