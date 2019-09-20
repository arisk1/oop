#include"fuction.h"

int good_thrsh, bad_thrsh;

int main(int argc, char *argv[])
{	int N, M, L;
	if(argc!=6)
    {
		cout << "you must give exactly 5 arguments!" << endl;
	}
	N=atoi(argv[1]);    //number of creatures
    M=atoi(argv[2]);    //number of times
    L=atoi(argv[3]);    //life
	good_thrsh=atoi(argv[4]);
	bad_thrsh=atoi(argv[5]);
	cout << endl;
	creature_society world(N, L);   //Create the creature society
	for(int i=0;i<M;i++)
    {
        if(rand()%2)    world.bless(rand()%N);
        else            world.beat(rand()%N);
	}
	if(world.no_of_good() == N)
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl <<"Good Dominates in the World!"<<endl<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	else if (world.no_of_zombie() == N)
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << "This is a dead society" << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	else
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl <<"Try again to improve the world"<<endl<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;
}
