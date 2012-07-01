#include <iostream>
using std::cout;
using std::endl;
#include <string>
#include <fstream>
#include <sstream>
using std::ifstream;
#include <vector>

std::string trim(std::string const& source, char const* delims = " \t\r\n;}<>") {
  std::string result(source);
  std::string::size_type index = result.find_last_not_of(delims);
  if(index != std::string::npos)
    result.erase(++index);

  index = result.find_first_not_of(delims);
  if(index != std::string::npos)
    result.erase(0, index);
  else
    result.erase();
  return result;
}

void print_string_vector(std::vector<std::string> myvector)
{
	for (int i = 0; i < myvector.size(); i++)
	{
		cout << "Vector[" << i << "] = " << myvector[i] << endl;
	}
}

void print_int_vector(std::vector<int> myvector)
{
	for (int i = 0; i < myvector.size(); i++)
	{
		cout << "Vector[" << i << "] = " << myvector[i] << endl;
	}
}

void print_vector_vector_int(std::vector< std::vector<int> > matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        if (matrix[i].size() != 0)
        {
            cout << "Ramo[" << i << "]: ";
            for (int j=0; j < matrix[i].size(); j++)
            {
                cout << matrix[i][j] << ",";
            }
            cout << endl;
        }
    }
}


int find_in_string_vector(std::string lost, std::vector<std::string> place)
{
	for (int i=0; i< place.size(); i++)
	{
		if ( place[i].compare(lost) == 0) return i;
	}
	return -1;
} // Works



int main(int argc, char const *argv[])
{
	ifstream file;
	file.open(argv[1]); // open a file
  	if (!file.good()) 
    	return 1; // exit if file not found
	
	// Helpers to parse
	std::string line;
	std::stringstream ss;
	int equal;
	int colon;
	std::string pre_value;

	//basics constants
	int p; //periodos
	int a; //min-load
	int b; //max-load
	int c; //min-courses
	int d; //max-courses

	bool more_const = true;
	while (more_const)
	{
		std::getline(file,line);
		if (! line.length()) continue;
	    if (line[0] == '/') continue;
    	if (line[0] == ' ') continue;
    	if (line[0] == '%') continue;

    	if (line[0] == 'p')
    	{
    		equal = line.find('=');
    		colon = line.find(';');
    		ss << trim(line.substr(equal+1,colon));
    		ss >> p;
    		ss.clear();
    	}

    	if (line[0] == 'a')
    	{
    		equal = line.find('=');
    		colon = line.find(';');
    		ss << trim(line.substr(equal+1,colon));
    		ss >> a;
    		ss.clear();
    	}
    	if (line[0] == 'b')
    	{
    		equal = line.find('=');
    		colon = line.find(';');
    		ss << trim(line.substr(equal+1,colon));
    		ss >> b;
    		ss.clear();
    	}
    	if (line[0] == 'c')
    	{
    		equal = line.find('=');
    		colon = line.find(';');
    		ss << trim(line.substr(equal+1,colon));
    		ss >> c;
    		ss.clear();
    	}
    	if (line[0] == 'd')
    	{
    		equal = line.find('=');
    		colon = line.find(';');
    		ss << trim(line.substr(equal+1,colon));
    		ss >> d;
    		ss.clear();
    		more_const = false;
    	}

	} //Works

	size_t found; //helper to find
	more_const = true;
	ss.clear(); //limpiar el stringstream
	std::vector<std::string> courses;
	std::string course;
	while (std::getline(file,line))
	{
		if (! line.length()) continue;
	    if (line[0] == '/') continue;
    	if (line[0] == ' ' && line.find("/") != std::string::npos) continue; //algunas pueden empezar vacias
    	if (line[0] == '%') continue;
    	if (line[0] == '}') break;
    	if (line[0] == ']') break;

    	found = line.find("courses");
    	if (found!=std::string::npos) continue; //ignorar la primera linea de courses;
    	
    	
    	ss << line; //transforma la linea en un stream

    	while(getline(ss,course,',')) //parsea ","
    	{
    		course = trim(course);
    		if (!course.length()) continue; // por si queda en blanco
    		courses.push_back(course);
    	}
    	ss.clear();
    	found = line.find("}");
    	if (found!=std::string::npos) break; //encontro un }, termina este bloeuque
	} //Works

	std::vector<int> credits;
	std::string credit;

	while (std::getline(file,line))
	{
		if (! line.length()) continue;
	    if (line[0] == '/') continue;
    	if (line[0] == ' ' && line.find("/") != std::string::npos) continue; //algunas pueden empezar vacias
    	if (line[0] == '%') continue;
    	if (line[0] == '}') break;
    	if (line[0] == ']') break;

    	found = line.find("credit");
    	if (found!=std::string::npos) continue; //ignorar la primera linea de courses;
    	
    	
    	ss << line; //transforma la linea en un stream
    	
    	while(getline(ss,credit,',')) //parsea ","
    	{
    		
    		credit = trim(credit);
    		if (! credit.length()) continue; //por si queda en blanco
    		std::stringstream ss_helper;
    		ss_helper << credit;
    		int to_vector;
    		ss_helper >> to_vector;
    		credits.push_back(to_vector);
    		ss_helper.clear();
    	}
    	
    	ss.clear();

    	found = line.find("]");
    	if (found!=std::string::npos) break; //encontro un }, termina este bloeuque
	} //Woks

    std::string master_course;
    std::string req_course;
    std::vector <std::vector <int> > prereq;
    prereq.resize(courses.size());
    while (std::getline(file,line))
    {
        if (! line.length()) continue;
        if (line[0] == '/') continue;
        if (line[0] == ' ' && line.find("/") != std::string::npos) continue; //algunas pueden empezar vacias
        if (line[0] == '%') continue;
        if (line[0] == '}') break;
        if (line[0] == ']') break;
        found = line.find("prereq");
        if (found!=std::string::npos) continue; //ignorar la primera linea de prereq;

        ss << line;

        while(getline(ss,course,','))
        {
            master_course = trim(course);
            if (!master_course.length()) continue;
            getline(ss,course,',');
            req_course = trim(course);
            if (!req_course.length()) continue;
            prereq[find_in_string_vector(master_course,courses)].push_back(find_in_string_vector(req_course,courses));
        }
        ss.clear();

        found = line.find("}");

        if (found != std::string::npos) break;

    }//Works
	return 0;
}