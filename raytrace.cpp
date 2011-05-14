/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */

#include <iostream>
#include <string>
#include "getopt.h"
#include "Scene.h"

using namespace std;

Scene *gTheScene;
string gProgramName;
int gResolution;

void usage( string message = "" ){
	cerr << message << endl;
	cerr << gProgramName << " -i <inputfile> -o <outputfile> -d <depthfile>" << endl;
	cerr << "          -or-" << endl;
	cerr << gProgramName << " --input <inputfile> --output <outputfile> --depth <depthfile>" << endl;
	
}

void parseCommandLine( int argc, char **argv ){
	int ch;
	string inputFile( "" ), outputFile( "" ), depthFile( "" );
	static struct option longopts[] = {
    { "input", required_argument, NULL, 'i' },
    { "output", required_argument, NULL, 'o' },
    { "depth", required_argument, NULL, 'd' },
    { "resolution", required_argument, NULL, 'r' },
    { "verbose", required_argument, NULL, 'v' },
    { "help", required_argument, NULL, 'h' },
    { NULL, 0, NULL, 0 }
	};

	while( (ch = getopt_long(argc, argv, "i:o:d:r:vh", longopts, NULL)) != -1 ){
		switch( ch ){
			case 'i':
				// input file
				inputFile = string(optarg);
				break;
			case 'o':
				// image output file
				outputFile = string(optarg);
				break;
			case 'd':
				// depth output file
				depthFile = string( optarg );
				break;
			case 'r':
        gResolution = atoi(optarg);
        break;
      case 'v':
        // set your flag here.
        break;
      case 'h':
        usage( );
        break;
			default:
				// do nothing
				break;
		}
	}
	gTheScene = new Scene( inputFile, outputFile, depthFile );
}

int main( int argc, char **argv ){
	string pathStr;
	gResolution = 512;
	gProgramName = argv[0];
	Magick::InitializeMagick(*argv);

	parseCommandLine( argc, argv );
	argc -= optind;
	argv += optind;
	if( gTheScene->hasInputSceneFilePath( ) &&
			gTheScene->hasOutputFilePath( ) &&
			gTheScene->hasDepthFilePath( ) ){
		gTheScene->parse( );	
		cout << *gTheScene << endl;	
		gTheScene->rayTrace(gResolution);
	}else{
		usage( "You specify an input scene file, an output file and a depth file." );
	}


	return( 0 );
}
