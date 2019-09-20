#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;


extern int good_thrsh, bad_thrsh;

class creature_society;

class creatureID
{	public:
        char *onom;
		int position;
};

class creature
{
	protected:
		creatureID name;
		int life;
		creature_society* mysociety;   //pointer to the society that the creature belongs
	public:
	    creature (const char*, const int, creature_society*);
		creature (const creature&);
		virtual ~creature(void)
		{
		     delete[] name.onom;
        }
		bool is_a_zombie(void)
		{
		    return !life;
        }
		virtual bool is_a_good(void)=0;
		virtual void clone(creature*&)=0;
		void beat(void);
		virtual void bless(void);
		int position(void);
};

class good_creature : public creature
{
    public:
        good_creature(const char* onoma,const int L,creature_society* society);
		~good_creature(void);
		void bless(void);
		bool is_a_good(void)
		{
		    return true;
        }
		void clone(creature*&);
};

class bad_creature : public creature
{	public:
        bad_creature(const char* onoma,const int L,creature_society* society);
		~bad_creature(void);
		void bless(void);
		bool is_a_good(void)
		{
		     return false;
        }
		void clone(creature*&);
};

class creature_society
{	int plithos;
	protected:
        creature** koinotita;   //array if pointers to creature
	public:
	    creature_society(const int, const int);
		~creature_society(void);
		void beat(int pst)
		{
		     koinotita[pst]->beat();
        }
		void bless(int pst)
		{
		     koinotita[pst]->bless();
        }
		void clone_next(int);
		void clone_zombies(int);
		int no_of_good(void);
		int no_of_zombie(void);
		int thesi(const creature*);
};
