#include "fuction.h"

/*---------------------------------------------NAMES FOR THE CREATURES---------------------------------------------*/
const char* goodnames[] = {
"Ross","Rachel","Monika","Bing","Chandler","Jooe","Phoeve","Whitebeard","Blackbeard","Ace","Zoro","Kaneki","Kirito","Asuna","Maka",
"BlackStar","Stein","Korositsuji","Yellowstar","Gildarts","Mirajane","Gray","Zeref","Misty","Ironclaw","Tirion","Deathwing","Warlock",
"King","Meliodas","Diane","Ban","Malfurion","Uthor","Merlin","Fireboy","Thunderlord","Fervor","Owari","Allen Walker","Millenium Earl",
};

const char* badnames[] = {
"Yu","Shinoa","Annie","Diana","Eduadro","Elizabeth","Biyakuya","Rukia","Rengi","Clockwise","Murloc","Equalitor","Consecratior","BanLord",
"Clawn","Ponnytail","Sasuke","Sirohige","Mugiwara","StormWind","Kururu","Asumaru","Akuma","Akame","SeventhSin","Azzuro","Brightess",
"Chronomachine","Posidon","Overlord","Kirino","Lawliet","Ryuzaki","Saber","Giglamesh","HolyGrail","Tauroas","Sagitarius","Kronos","Gemini",
"BIGEGG","Lucif","Momento","Mamga","Trompone","Rango","Suuuuuper","cidi","Thorrisan","Ragnaros","Platiman","Diamante","ShinyGolderGod",
};

/*---------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------Creature------------------------------*/

creature::creature(const char* onoma, const int L, creature_society* society)
{
    mysociety = society;
	delete[] name.onom;
	name.onom = new char[strlen(onoma)+1];
	strcpy(name.onom, onoma);
	name.position = -1;				//-1 cause it doesnt belong to [0,N-1]
	life=L;
}

creature::creature(const creature &crtr)
{
    name.onom = new char[strlen(crtr.name.onom)+1];
	strcpy(name.onom,crtr.name.onom);
	name.position = -1;
	life = crtr.life;
	mysociety = crtr.mysociety;
	cout <<  crtr.name.onom <<"(pos:"<< crtr.name.position <<")"<< " was cloned"<<endl << endl;
}

void creature::bless(void)
{
    cout << "Bless the creature:" << name.onom <<"(pos:"<< position() <<"-lifePoints:"<<life<<")" << endl;
	if (!is_a_zombie())	life++;	    //if the creature isnt a zombie then add 1 life point to it
	else		cout << "Zombies can't be blessed" << endl;
}

void creature::beat(void)
{
    cout << "Beat the creature:" << name.onom <<"(pos:"<< position() <<"-lifePoints:"<<life<<")" << endl;
	if (!is_a_zombie())	life--; //if the creature isnt a zombie reduce his life points by 1
	else		cout << "Zombies can't be beaten." << endl;
	cout << name.onom <<"(pos:"<< position() <<")"<< "has now " << life << " life points "<< endl <<endl;
}

int creature::position(void)
{
    if(name.position==-1)	name.position= mysociety->thesi(this);     //if name.position != -1 do nothing, else fine the position of ''this''
	return name.position;
}

/*------------------------------GoodCreature------------------------------*/


good_creature::good_creature(const char* onoma,const int L,creature_society* society):creature(onoma,L,society)
{
    cout <<"Creature with name:"<< name.onom << " and " << life << " life points" << " -> good was created" << endl;
}

good_creature::~good_creature(void)
{
	if (life>0)     cout << "good creature with name:" << name.onom <<"(pos:"<< position() <<")"<<" and " << life << " life points is being destroyed"<< endl;
	else            cout << "zombie with name:"<< name.onom << position() << " and " << life << " life points is being destroyed" << endl;
}

void good_creature::bless(void)
{
    creature::bless();
    cout << name.onom <<"(pos:"<< position() <<")"<< "has now " << life << " life points "<< endl <<endl;
	if(life>good_thrsh)		mysociety->clone_next(position()-1);
}

void good_creature::clone(creature* &c)
{
cout << name.onom <<"(pos:"<< position() <<")"<< " will be cloned" << endl;
	delete c;   //destroy the previous creature
	c = new good_creature(*this);
}

/*------------------------------BadCreature------------------------------*/

bad_creature::bad_creature(const char* onoma,const int L,creature_society* society):creature(onoma,L,society)
{
    cout <<"Creature with name:"<< name.onom << " and " << life << " life points" << " -> bad was created" << endl;
}

bad_creature::~bad_creature(void)
{
	if (life>0) cout << "bad creature with name:" << name.onom <<"(pos:"<< position() <<")"<<" and " << life << " life points is being destroyed"<< endl;
	else		cout << "zombie with name:"<< name.onom << position() << " and " << life << " life points is being destroyed" << endl;
}

void bad_creature::bless(void)
{	creature::bless();
	cout << name.onom <<"(pos:"<< position() <<")"<< "has now " << life << " life points "<< endl <<endl;
	if(life>bad_thrsh)		mysociety->clone_zombies(position()-1);
}

void bad_creature::clone(creature* &c)
{
    cout << name.onom <<"(pos:"<< position() <<")"<< " will be cloned" << endl;
	delete c;
	c = new bad_creature(*this);
}



/*------------------------------CreatureSociety------------------------------*/

creature_society::creature_society(const int N, const int L)
{
    int creatureNames=sizeof(goodnames)/sizeof(char*);   //length of the array
	plithos = N;
	koinotita=new creature* [plithos];
	for(int i=0;i<plithos;i++)
    {
		if(rand()%2)
        koinotita[i]=new good_creature(goodnames[rand()%creatureNames], L, this);    //create a good creature
		else
        koinotita[i]=new bad_creature(badnames[rand()%creatureNames], L, this);  //create bad creature
		cout<< "Creature's position :" << koinotita[i]->position() << endl;
	}
	cout<<endl;
	cout<<"* - * - * - * - * - * - * - * - * - *"<<endl;
	cout << "Creature Society is ready" << endl;
    cout<<"* - * - * - * - * - * - * - * - * - *"<<endl;
    cout<<endl;
}

creature_society::~creature_society(void)
{
    for(int i=0;i<plithos;i++)
    delete koinotita[i];    //destroy one of the creatures
	delete [] koinotita;
	cout << "Creature Society is destroyed" << endl;
}

void creature_society::clone_next(int pst)
{
    koinotita[pst]->clone(koinotita[(pst+1)%plithos]);
}

void creature_society::clone_zombies(int pst)
{
    int i=pst+1;
	while(i<plithos && koinotita[i]->is_a_zombie())
    koinotita[pst]->clone(koinotita[i++]);
}

int creature_society::no_of_good(void)  //counter for the good creatures that arent zombies
{
    int number=0;
	for(int i=0;i<plithos;i++)
    if(koinotita[i]->is_a_zombie() == false && koinotita[i]->is_a_good() == true)
        number++;
	return number;
}

int creature_society::no_of_zombie(void)
{	int number=0;
	for(int i=0;i<plithos;i++)
    if(koinotita[i]->is_a_zombie() == true)
			number++;
	return number;
}

int creature_society::thesi(const creature* myself)		//finds this to the array
{
    for(int i=0; i<plithos ;i++)
		if(koinotita[i] == myself)  return i+1;
}
