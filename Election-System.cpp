#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Person
{
	protected:
		string name;
		int cnic;
		string Province;
		string gender;
	public:
		Person(string name="unfilled",int cnic=0,string prov="no-data",string gen="un-declared")
		{
			this->name=name;
			this->cnic=cnic;
			Province=prov;
			gender=gen;
		}
		void setname(string n)
		{
			name=n;
		}
		void setCnic(int i)
		{
			cnic=i;
		}
		void setProvince(string prov)
		{
			Province=prov;
		}
		void setGender(string gen)
		{
			gender=gen;
		}
		string getname()
		{
			return name;
		}
		int getCnic()
		{
			return cnic;
		}
		string getProvince()
		{
			return Province;
		}		
		string getGender()
		{
			return gender;
		}
};

class Voter:public Person
{
	private:
		static int id; 
		bool VoteStatus;
		string password;
		int VoterID;
		
	public:
		Voter(bool voteS=false,string pass="NO data",int vID=0000,string name="unfilled",int c=0,string prov="no-data",string gen="un-declared"):Person(name,c,prov,gen)
		{
			VoteStatus=voteS;
			password=pass;
			VoterID=vID;
		}
		int voterID()
		{
			return VoterID;
		}
		void SetVoterID()
		{
			id=id+1;
			VoterID=id;
		}
		void SetVoterIDDirect(int vid)
		{
			VoterID=vid;
			if(vid>id) 
			id=vid;
		}
		void DeleteVoterID(int vi)
		{
			if(vi==VoterID)
			{
				VoterID=0;
			}
		}
		void setStatus(bool status)
		{
			VoteStatus=status;	
		}
		bool getStatus()
		{
			return VoteStatus;
		}
		string getPassword()
		{
			return password;
		}
		static int getStaticID()
		{
			return id;
		}
		static void setStaticID(int val)
		{
			id=val;
		}
};
int Voter::id=122;

class Candidate:public Person
{
	private:
		int CandidateID;
		string party;
		int votes;
		static int id;
	public:
	 Candidate(int votes=0,int cid=0000,string party="None",string name="unfilled",int cnic=0,string nat="no-data",string gen="un-declared"):Person(name,cnic,nat,gen)
	 {
	 	this->votes=votes;
	 	CandidateID=cid;
	 	this->party=party;
	 }
	 int getVotes()
	 {
	 	return votes;
	 }
	 int getcanID()
	 {
	 	return CandidateID;
	 }
	 void setcanID()
	 {
	 	id=id+1;
		CandidateID=id;
	 }
	 void setcanIDDirect(int cid)
	 {
	 	CandidateID=cid;
	 	if(cid>id) id=cid;
	 }
	 void setvotes()
	 {
	 	votes=votes+1;
	 }
	 void setparty()
	 {
	 	party="None";
	 }
	 string getParty()
	 {
	 	return party;
	 }
	 static int getStaticID()
	 {
	 	return id;
	 }
	 static void setStaticID(int val)
	 {
	 	id=val;
	 }
};
int Candidate::id=0;

// ---------------------------------------------
// Global Arrays
// ---------------------------------------------
Voter Varray[100];
int numVo=0;

Candidate Carray[50];
int numCnd=0;
int ccount=0;

// ---------------------------------------------
// FILE HANDLING FUNCTIONS
// ---------------------------------------------

// Save ALL voters currently in Varray to voters.txt
void saveVoters()
{
	ofstream file("voters.txt");
	if(!file)
	{
		cout<<"\nError: Could not open voters.txt for writing!";
		return;
	}
	for(int i=0;i<100;i++)
	{
		if(Varray[i].getCnic()!=0)
		{
			file<<Varray[i].getname()<<"\n";
			file<<Varray[i].getCnic()<<"\n";
			file<<Varray[i].getProvince()<<"\n";
			file<<Varray[i].getGender()<<"\n";
			file<<Varray[i].voterID()<<"\n";
			file<<Varray[i].getPassword()<<"\n";
			file<<Varray[i].getStatus()<<"\n";
			file<<"---\n"; // separator between voters
		}
	}
	file.close();
}

// Load ALL voters from voters.txt into Varray
void loadVoters()
{
	ifstream file("voters.txt");
	if(!file)
	{
		// File doesn't exist yet — load hardcoded defaults and save them
		Varray[0]=Voter(false,"abcdefg",0,"Arham",42042042,"Punjab","Male");
		Varray[0].SetVoterID();
		Varray[1]=Voter(false,"hijklmn",0,"Qasim",561647,"Punjab","Male");
		Varray[1].SetVoterID();
		Varray[2]=Voter(false,"opqrst",0,"Mehdi",420024,"Punjab","Male");
		Varray[2].SetVoterID();
		Varray[3]=Voter(false,"uvwx",0,"Ahsan",5665474,"Punjab","Male");
		Varray[3].SetVoterID();
		Varray[4]=Voter(false,"yzabc",0,"Khan",804321,"Punjab","Male");
		Varray[4].SetVoterID();
		numVo=5;
		saveVoters(); // create the file for next time
		cout<<"\nvoters.txt created with default voters.";
		return;
	}

	string line;
	int i=0;
	while(i<100)
	{
		string vname,vprov,vgend,vpass;
		int vcnic,vid;
		bool vstatus;

		if(!getline(file,vname)) break;
		if(vname=="---"){continue;} // skip stray separators

		file>>vcnic; file.ignore();
		getline(file,vprov);
		getline(file,vgend);
		file>>vid; file.ignore();
		getline(file,vpass);
		file>>vstatus; file.ignore();
		getline(file,line); // consume "---"

		// Find empty slot in array
		for(int j=0;j<100;j++)
		{
			if(Varray[j].getCnic()==0)
			{
				Varray[j]=Voter(vstatus,vpass,0,vname,vcnic,vprov,vgend);
				Varray[j].SetVoterIDDirect(vid);
				numVo++;
				break;
			}
		}
		i++;
	}
	file.close();
}

// Save ALL candidates currently in Carray to candidates.txt
void saveCandidates()
{
	ofstream file("candidates.txt");
	if(!file)
	{
		cout<<"\nError: Could not open candidates.txt for writing!";
		return;
	}
	for(int i=0;i<50;i++)
	{
		if(Carray[i].getCnic()!=0 && Carray[i].getname()!="unfilled")
		{
			file<<Carray[i].getname()<<"\n";
			file<<Carray[i].getCnic()<<"\n";
			file<<Carray[i].getProvince()<<"\n";
			file<<Carray[i].getGender()<<"\n";
			file<<Carray[i].getcanID()<<"\n";
			file<<Carray[i].getParty()<<"\n";
			file<<Carray[i].getVotes()<<"\n";
			file<<"---\n"; // separator between candidates
		}
	}
	file.close();
}

// Load ALL candidates from candidates.txt into Carray
void loadCandidates()
{
	ifstream file("candidates.txt");
	if(!file)
	{
		// File doesn't exist yet — load hardcoded defaults and save them
		Carray[0]=Candidate(0,0,"D.O.N","Saqib",234234,"Punjab","Male");
		Carray[0].setcanID();
		Carray[1]=Candidate(0,0,"M.P.M","Humiayun",453425,"Punjab","Male");
		Carray[1].setcanID();
		Carray[2]=Candidate(0,0,"K.O.N","Talha",450002,"Punjab","Male");
		Carray[2].setcanID();
		Carray[3]=Candidate(0,0,"B.B.Q","Akram",123002,"Punjab","Male");
		Carray[3].setcanID();
		Carray[4]=Candidate(0,0,"K.P.L","Gujjar",45653,"Punjab","Female");
		Carray[4].setcanID();
		numCnd=5;
		saveCandidates(); // create the file for next time
		cout<<"\ncandidates.txt created with default candidates.";
		return;
	}

	string line;
	int i=0;
	while(i<50)
	{
		string cname,cprov,cgend,cparty;
		int ccnic,ccid,cvotes;

		if(!getline(file,cname)) break;
		if(cname=="---"){continue;}

		file>>ccnic; file.ignore();
		getline(file,cprov);
		getline(file,cgend);
		file>>ccid; file.ignore();
		getline(file,cparty);
		file>>cvotes; file.ignore();
		getline(file,line); // consume "---"

		for(int j=0;j<50;j++)
		{
			if(Carray[j].getCnic()==0)
			{
				Carray[j]=Candidate(cvotes,0,cparty,cname,ccnic,cprov,cgend);
				Carray[j].setcanIDDirect(ccid);
				numCnd++;
				break;
			}
		}
		i++;
	}
	file.close();
}

// ---------------------------------------------
// ELECTION COMMISSION
// ---------------------------------------------
void Election_Commision()
{
	int e;int cnic;string name,password,province,gender;string yn,party;
	cout<<"\n----------";
	cout<<"\nElection Commision";
	cout<<"\n----------";
	cout<<"\nFunctions:";
	cout<<"\n1.Add Voter\n2.Remove Voter\n3.Add Candidate\n4.Remove Candidate\n5.Display\nAny to return \nEnter your choice:";
	cin>>e;
		
		if(e==1)
		{
			cout<<"\nEnter the Name of voter:";
			cin.ignore();
			getline(cin,name);
			cout<<"\nEnter your Cnic Number:";
			cin>>cnic;
			for(int i=0;i<100;i++)
			{
				if(cnic==Varray[i].getCnic())
				{
					cout<<"\n----------";
					cout<<"\nVoter Already exists on this CNIC!!";
					cout<<"\n----------\n";
					return;
				}
			}
			
			cout<<"\nset a password for your profile:";
			cin.ignore();
			getline(cin,password);
			cout<<"Enter your Province:";
			getline(cin,province);
			cout<<"\nEnter Your Gender:";
			getline(cin,gender);
			
			for(int i=0;i<100;i++)
			{
				if(Varray[i].getCnic()==0)
				{
					Varray[i]=Voter(false,password,0,name,cnic,province,gender);
					Varray[i].SetVoterID();
					cout<<"\nVoter Added To The list:\nName: "<<Varray[i].getname();
					cout<<"\nCNIC:"<<Varray[i].getCnic();
					cout<<"\nVoter-ID:"<<Varray[i].voterID();
					cout<<"\nProvince:"<<Varray[i].getProvince();
					cout<<"\nGender:"<<Varray[i].getGender();
					numVo++;
					saveVoters(); // ? Save to file after adding
					break;
				}
				else
				{
					continue;
				}
			}
		}
		else if(e==2)
		{	
			int vi;string pass;
			cout<<"\nEnter Your Voter ID: ";
			cin>>vi;
			cout<<"\nEnter Your Password: ";
			cin.ignore();
			getline(cin,pass);
			bool voterDeleted=false;
			for(int i=0;i<100;i++)
			{
				if(vi==Varray[i].voterID()&&pass==Varray[i].getPassword())
				{
					Varray[i].setname("unfilled");
					Varray[i].setCnic(0);
					Varray[i].setProvince("no-data");
					Varray[i].setGender("un-declared");
					Varray[i].DeleteVoterID(vi);
					cout<<"\n----------";
					cout<<"\nThe VOTER Has Been Deleted";
					cout<<"\n----------\n";
					--numVo;
					voterDeleted=true;
					saveVoters(); // ? Save to file after deleting
					break;
				}
			}
			if(!voterDeleted)
			{
				cout<<"\n----------";
				cout<<"\nThe Voter Credentials Didn't Match or Don't Exist";
				cout<<"\n----------\n";
			}
		}
		else if(e==3)
		{
			cout<<"\nEnter the Name of Candidate:";
			cin.ignore();
			getline(cin,name);
			cout<<"\nEnter Candidate Cnic Number:";
			cin>>cnic;
			cout<<"\nEnter Province:";
			cin.ignore();
			getline(cin,province);
			cout<<"\nEnter Gender:";
			getline(cin,gender);
			cout<<"\nEnter(Political Party/Indipendent): ";
			getline(cin,party);
			ccount=ccount+1;
			for(int i=0;i<50;i++)
			{
				if(Carray[i].getname()=="unfilled")
				{
					Carray[i]=Candidate(0,0,party,name,cnic,province,gender);
					Carray[i].setcanID();
					cout<<"\n----------";
					cout<<"\nCandidate Added To The list:";
					cout<<"\n----------";
					cout<<"\nName: "<<Carray[i].getname();
					cout<<"\nCandidate-ID:"<<Carray[i].getcanID();
					cout<<"\nCNIC:"<<Carray[i].getCnic();
					cout<<"\nParty:"<<Carray[i].getParty();
					cout<<"\nProvince:"<<Carray[i].getProvince();
					cout<<"\nGender:"<<Carray[i].getGender();
					numCnd++;
					saveCandidates(); // ? Save to file after adding
					break;
				}
				else
				{
					continue;
				}
			}
		}
		else if(e==4)
		{	
			int cid;
			cout<<"\n----------";
			cout<<"\nEnter the candidate ID you want to delete:";
			cin>>cid;
			bool found=false;
			for(int i=0;i<50;i++)
			{
				if(cid==Carray[i].getcanID())
				{
					found=true;
					Carray[i]=Candidate();
					cout<<"\n----------";
					cout<<"\nThe Candidate Has Been Deleted";
					cout<<"\n----------\n";
					--numCnd;
					saveCandidates(); // ? Save to file after deleting
					break;
				}
			}
			if(found!=true)
			{
				cout<<"\nInvalid Candidate ID\n";
			}
		}
		else if(e==5)
		{
			cout<<"\n--------------------";
			cout<<"\nVoter Details:";
			cout<<"\n--------------------";
			for(int i=0;i<100;i++)
			{
				if(Varray[i].getCnic()!=0)
				{
					cout<<"\nName:"<<Varray[i].getname();
					cout<<"\nVoter-ID:"<<Varray[i].voterID();
					cout<<"\nCnic:"<<Varray[i].getCnic();
					cout<<"\nProvince:"<<Varray[i].getProvince();
					cout<<"\nGender:"<<Varray[i].getGender();
					if(Varray[i].getStatus()==true)
					{
						cout<<"\nVote Status: Voted!!!";
					}
					else
					{
						cout<<"\nVote Status: Didn't Vote!!!";
					}
					cout<<"\n--------------------\n";
				}
				else
				{
					continue;
				}
			}
			cout<<"\n--------------------";
			cout<<"\nCandidate Details:";
			cout<<"\n--------------------\n";
			for(int a=0;a<50;a++)
			{
				if(Carray[a].getCnic()!=0)
				{
					cout<<"\nName:"<<Carray[a].getname();
					cout<<"\nCandidate-ID:"<<Carray[a].getcanID();
					cout<<"\nCnic:"<<Carray[a].getCnic();
					cout<<"\nProvince:"<<Carray[a].getProvince();
					cout<<"\nGender:"<<Carray[a].getGender();
					cout<<"\nParty:"<<Carray[a].getParty();
					cout<<"\nNo.of Votes:"<<Carray[a].getVotes();
					cout<<"\n--------------------\n";
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			return;			
		}
}

// ---------------------------------------------
// CAST VOTE
// ---------------------------------------------
void Cast_Vote()
{	
	int ci;string pass;int c;
	cout<<"\nEnter Your CNIC:";
	cin>>ci;
	cout<<"\nEnter your Password: ";
	cin>>pass;
	bool userFound=false;
	for(int v=0;v<100;v++)
	{
		if(ci==Varray[v].getCnic()&&pass==Varray[v].getPassword())
		{
			userFound=true;
			if(Varray[v].getStatus()==false)
			{
				cout<<"Welcome MR."<<Varray[v].getname()<<"\nVoter ID"<<Varray[v].voterID();
				cout<<"\n------------------------------------";
				cout<<"\nCanditates |||\tParty  |||\tProvince";
				cout<<"\n------------------------------------";
				for(int i=0;i<50;i++)
				{
					if(Carray[i].getParty()!=""&&Carray[i].getname()!="unfilled")
					{
						cout<<"\n"<<Carray[i].getcanID()<<"."<<Carray[i].getname()<<"    \t"<<Carray[i].getParty()<<"    \t"<<Carray[i].getProvince();
					}
					else
					{
						continue;
					}
				}
				cout<<"\nSelect your Candidate:";
				cin>>c;
				for(int ca=0;ca<50;ca++)
				{
					if(c==Carray[ca].getcanID())
					{
						Carray[ca].setvotes();
						Varray[v].setStatus(true);
						cout<<"\nYour vote has been casted to Mr/Mrs."<<Carray[ca].getname();
						saveVoters();     // ? Update voter status in file
						saveCandidates(); // ? Update candidate vote count in file
						break;
					}
					else
					{
						continue;
					}
				}
			}
			else
			{
				cout<<"\n--------------------";
				cout<<"\nYou have Already Voted!!";
				cout<<"\n--------------------\n";
				break;
			}
		}
	}
	if(!userFound)
	{
		cout<<"\n--------------------";
		cout<<"\nYour Password or CNIC is Incorrect!!";
		cout<<"\n--------------------\n";
	}
}

// ---------------------------------------------
// ELECTION RESULTS
// ---------------------------------------------
void Election_Results()
{
	int w=-1;string wn;
	for(int i=0;i<50;i++)
	{
		if(Carray[i].getname()!="unfilled"&&Carray[i].getVotes()>w)
		{
			w=Carray[i].getVotes();
			wn=Carray[i].getname();
		}
	}
	if(w<=0) 
	{
		cout<<"\n----------";
		cout<<"\n----------";
		cout<<"\nThe Elections Havent been Conducted!!";
		cout<<"\n----------";
		cout<<"\n----------\n";
	}
	else
	{ 	
		cout<<"\n----------";
		cout<<"\n----------";
		cout<<"\nThe Winner of this Elections is Mr/Mrs."<<wn<<"\nWinning with "<<w<<" Votes";
		cout<<"\n----------";
		cout<<"\n----------\n";
	}
}

// ---------------------------------------------
// MAIN
// ---------------------------------------------
int main()
{
	// Load data from files (creates files with defaults if they don't exist)
	loadVoters();
	loadCandidates();

	int c;
	cout<<"\n---Welcome to Election Managment System---";
	do{
		cout<<"\n1.Election Commision\n2.Cast Vote\n3.Election Results\nAny Number to close program";
		cout<<"\nEnter your choice:";
		cin>>c;

		if(c==1)
		{
			Election_Commision();	
		}
		else if(c==2)
		{
			Cast_Vote();
		}
		else if(c==3)
		{
			Election_Results();
		}
		else
		{
			break;
		}
	}while(true);

	return 0;
}
