#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


char *
basename(char *path)
{
    char *base = strrchr(path, '/');

    return base ? (1+base) : path;
}

char *pgm;

void
usage(int rc)
{
    fprintf(stderr, "usage: %s [-s STACK] HTA HT-LENGTH [STEM-LENGTH]\n", pgm);
    exit(rc);
}


int
main(argc, argv)
char **argv;
{
    float hta;
    float htlength;
    float stack = 35;
    float stemlength;
    float offset;
    
    int c;
    int accept_anything = 0;


    opterr = 1;
    pgm = basename(argv[0]);

    while ( (c=getopt(argc, argv, "?fs:")) != EOF )
	switch (c) {
	case 's':   stack = atof(optarg);
		    break;
	case 'f':   accept_anything = 1;
		    break;
	default:    usage( (c == '?') ? 0 : 1 );
		    break; /* not reached */
	}

    argc -= optind;
    argv += optind;

    if ( argc < 2 || argc > 3 )
	usage(1);

    hta = atof(argv[0]);
    htlength = atof(argv[1]);
    stemlength = (argc == 3) ? atof(argv[2]) : 100;

    if ( !accept_anything ) {
	if ( hta < 60 ) {
	    fprintf(stderr, "%s: hta %.0f < 60? (use -f to allow)\n",
			    pgm, hta);
	    exit(1);
	}
	if ( htlength < 30 ) {
	    fprintf(stderr, "%s: ht length %.0f < 30? (use -f to allow)\n",
			     pgm, htlength);
	    exit(1);
	}
	if ( stemlength < 30 ) {
	    fprintf(stderr, "%s: stem length %.0f < 30? (use -f to allow)\n",
			    pgm, stemlength);
	    exit(1);
	}
    }

    hta = M_PI * (hta / 180);

    offset = stemlength-(cos(hta)*(htlength+stack));

    printf("deck offset is %.0f\n", offset < 0 ? 0 : offset);
}
