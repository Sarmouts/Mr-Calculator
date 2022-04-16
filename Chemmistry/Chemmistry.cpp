#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

typedef unsigned int uint;

std::unordered_map<std::string, uint> Ar = {
{"H",1},
{"He",4},
{"Li",7 },
{"Be",9},
{"B",11} ,
{"C",12},
{"N",14},
{"O",16},
{"F",19},
{"Ne",20},
{"Na",23},
{"Mg",24},
{"Al",27},
{"Si",28},
{"P",31},
{"S",32},
{"Cl",35},
{"K",39},
{"Ar",40},
{"Ca",40},
{"Sc",45},
{"Ti",48},
{"V",51},
{"Cr",52},
{"Mn",55},
{"Fe",56},
{"Ni",59},
{"Co",59},
{"Cu",64},
{"Zn",65},
{"Ga",70},
{"Ge",73},
{"As",75},
{"Se",79},
{"Br",80},
{"Kr",84},
{"Rb",85},
{"Sr",88},
{"Y",89},
{"Zr",91},
{"Nb",93},
{"Mo",96},
{"Tc",98},
{"Ru",101},
{"Rh",103},
{"Pd",106},
{"Ag",108},
{"Cd",112},
{"In",115},
{"Sn",119},
{"Sb",122},
{"I",127},
{"Te",128 },
{"Xe",131},
{"Cs",133},
{"Ba",137},
{"La",139},
{"Ce",140},
{"Pr",141},
{"Nd",144},
{"Pm",145},
{"Sm",150},
{"Eu",152},
{"Gd",157},
{"Tb",159},
{"Dy",163 },
{"Ho" ,165},
{"Er",167},
{"Tm",169},
{"Yb", 173},
{"Lu",175},
{"Hf",178},
{"Ta",181},
{"W",184},
{"Re",186},
{"Os",190},
{"Ir",192},
{"Pt",195},
{"Au",197},
{"Hg",201},
{"Tl",204},
{"Pb",207 },
{"Bi",209},
{"Po",209},
{"At",210},
{"Rn",222},
{"Fr",223},
{"Ra",226},
{"Ac",227},
{"Pa",231},
{"Th",232},
{"Np",237},
{"U",238},
{"Am",243},
{"Pu",244},
{"Cm",247},
{"Bk",247},
{"Cf",251},
{"Es",252},
{"Fm",257},
{"Md",258},
{"No",259},
{"Rf",263},
{"Lr",262},
{"Db",268},
{"Bh",270},
{"Sg",271},
{"Mt",278},
{"Rg",281},
{"Hs",270},
{"Ds",281},
{"Cn",285},
{"Nh",286},
{"Fl",289},
{"Mc",289},
{"Lv",293},
{"Ts",294},
{"Og",294}
};

std::string RemovePareth(std::string str)
{
	std::string result = "";
	std::string temp = "";
	uint syn = 0;
	bool isCap, isnum;
	for (uint i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			auto f = str.find(')', i);
			temp = str.substr(i + 1, (f - 1) - i);
			syn = str[f + 1] - '0';
			for (uint j = 0; j < temp.length(); j++)
			{
				isCap = temp[j] == toupper(temp[j]);
				isnum = std::to_string(temp[j] - '0').length() == 1;
				if (isnum)
					result += std::to_string(syn * (temp[j] - '0'));
				else if (isCap && j - 1 != -1)
				{
					if (!(std::to_string(temp[j - 1] - '0').length() == 1))
						result += std::to_string(syn) + temp[j];
					else
						result += temp[j];
				}
				else
					result += temp[j];
			}
			i = f + 1;
		}
		else
			result += str[i];
	}
	return result;
}
void WriteMolecule(std::string molecule)
{
	std::ofstream temp{ "temp.txt" };
	bool isnum, isSmall;
	for (uint i = 0; i < molecule.length(); i++)
	{
		temp << molecule[i];
		if (std::to_string(molecule[i] - '0').length() == 1)
			continue;
		isSmall = molecule[i + 1] == tolower(molecule[i + 1]);
		isnum = std::to_string(molecule[i + 1] - '0').length() == 1;
		if (!(isSmall))
			temp << " 1";
		else if (isnum)
			temp << " ";
		else if (i + 1 == molecule.length())
			temp << " 1";
	}
	temp.close();
}
uint Mr(std::string mlc)
{
	std::ifstream read{ "temp.txt" };
	std::string element;
	uint num = 0;
	uint MolMass = 0;
	while (read >> element >> num)
		MolMass += num * Ar[element];
	read.close();
	return MolMass;
}
int main()
{
	std::string molecule;
	std::cout << "Enter Mr";
	std::cin >> molecule;
	WriteMolecule(RemovePareth(molecule));
	std::cout << "Mr(" << RemovePareth(molecule) << ") = " << Mr(molecule) << "amu";
}