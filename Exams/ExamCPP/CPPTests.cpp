/**
 * \brief The following program reads from the CLI a list of students. Each student has a first name and grades average.
 * Then, the program outputs the student that has the highest grades average. If there're more than one student, it'll
 * output the first one.
 */

#include <iostream>
#include <chrono>
#include "Point.cpp"
#include <string>
#include "VLVector.hpp"
#include <algorithm>
#include "Student.cpp"

using std::string;
using std::sort;

/** \brief The vector static capacity. */
#define STATIC_CAPACITY 16


static string names1[] = {"Haim", "Betty", "Shelly", "Yuval", "Neema", "Eden", "Rina", "Itay",
						  "Avisahi", "Molly", "Netta", "Leo", "Chen", "Yuval", "Tobby",
						  "Sabrina",
						  "Valery", "Ana", "Yehud", "Tal", "Herzel", "Molly", "Geva", "Ido",
						  "Aya", "Sara", "Tomer", "Avital", "Arni", "Shany", "Or", "Hila",
						  "Or", "Minna", "Zila"};
static int grades1[] = {24, 53, 45, 45, 78, 67, 53, 45, 78, 23, 13, 98, 90, 65, 45, 24, 45, 46, 21,
						76, 65, 46, 23, 76,
						32, 45, 45, 89, 23, 54, 87, 23, 65, 98, 32, 65, 8, 45, 98, 56, 23, 56, 78,
						98, 54, 23, 87, 23, 12,
						43, 37, 67, 24, 69, 74, 83};
static string names2[] = {"Esme Cline", "Rheanna Cruz", "Leanna Brook", "Jaya Alfaro",
						  "Rhianne Odonnell",
						  "Izabella Brown", "Fannie Cohen", "Lucian Weston", "Seth Orr",
						  "Erik Webb", "Bonnie Schmitt", "Natalie Mccarty", "Rose Lyons",
						  "Tayyibah Montgomery", "Jaheim Riggs", "Adeline John",
						  "Shaan Barr", "Lillie-May Thorpe", "Simone Driscoll",
						  "Konnor Rosario", "Maha Oconnell", "Aliyah Waller", "Akeel Betts",
						  "Hettie Adam", "Amber Noel", "Adrienne Stephens", "Mirza Hanson",
						  "Luna Hastings", "Kodi Norton", "Sophie Leigh", "Addison Cortez",
						  "Blythe Ramsey", "Riyad Woolley", "Abida Ferguson", "Silas Ferry",
						  "Iestyn Novak", "Montague Henry", "Olive Brock", "Kadeem Devine",
						  "Areebah Fulton", "Emir Rudd", "Findlay Iles", "Elizabeth Lozano",
						  "Bree Mckenzie", "Jozef Nairn", "Ahmad Bowen", "Jordon Keeling",
						  "Raife Andrew", "Lacy Madden", "Megan Colon", "Audrey Mckinney",
						  "Niall Clay", "Reema Washington", "Dominique Mullen", "Yuvaan Heath",
						  "Mihai Robin", "Darla Simmons", "Marco Fuller", "Bethanie Rowe",
						  "Thiago Valencia", "Mariam Simon", "Guy Dale", "Lina Mcdougall",
						  "Daisie Ferrell", "Phillip Anthony", "Johnathan Doyle",
						  "Aleesha Christian", "Kade Bouvet", "Jeremy Maddox", "Arla Rocha",
						  "Saba Becker", "Aarron Harrington", "Ayub Sutherland", "Maximus Witt",
						  "Rohaan Medina", "Herbert Muir", "Christian Rahman", "Elliott Pate",
						  "Libbi Swanson", "Mehreen Kelley", "Osman Campbell", "Kasper Conway",
						  "Roger Fox", "Kobe Morris", "Samuel Maldonado", "Enzo Pike",
						  "Maysa Blackmore", "Richard Khan", "Chester Hays", "Wilf Hodgson",
						  "Hebe Rankin", "Darcy Braun", "Ariyan Fleming", "Rabia Lang",
						  "Paloma Levy", "Niamh Browne", "Issa Malone", "Anayah Jones",
						  "Dollie Frederick", "Malika Hodge", "Tony Mckeown", "Mylie Humphrey",
						  "Warwick Griffith", "Tillie Marks", "Samiya Osborne", "Helin Larsen",
						  "Joni Robinson", "Essa Finnegan", "Ariella Hilton", "Misha Lambert",
						  "Rome Leblanc", "Aimee Deacon", "Nabil Roberts", "Mateo Hamilton",
						  "Riley Guzman", "Fraser Enriquez", "Louise Sheehan",
						  "Billy-Joe Partridge", "Danniella Callahan", "Evelina Trejo",
						  "Tamzin Maldonado", "Honey Hickman", "Miruna Mathews", "Alejandro Sexton",
						  "Maliha Christie", "Russell Hudson", "Shae Holland", "Ryley Calvert",
						  "Magdalena Huff", "Ishaan Cottrell", "Harvir Haas", "Ibrar Handley",
						  "Claude Cresswell", "Alexandria Meyer", "Kayley Andersen",
						  "Alicja Doherty", "Siya Ramsay", "Ajay Webster", "Timothy Mata",
						  "Alfred Sharp", "Eisa Mann", "Karla Brock", "Jiya Wade", "Ivo Dixon",
						  "Tilly-Mae Crowther", "Bella-Rose Moran", "Hakim Hook",
						  "Ananya Hernandez", "Neave Aguirre", "Havin Wiley", "Madeeha Suarez",
						  "Layan Hammond", "Deon Cruz", "Aleah Bates", "Jensen Conway",
						  "Ashton Benton", "Austin Farrell", "Tyler-Jay Carroll", "Savanna Levine",
						  "Tierney Whitehouse", "Jannah Nelson", "Alyce Yang", "Jordana Hess",
						  "Sahil Kline", "Aronas Connor", "Akram Copeland", "Gabrielle Hyde",
						  "Ronan Cairns", "Shannen Travis", "Tanvir Avalos", "Bailey Crosby",
						  "Kajol Dodson", "Khadija Childs", "Kane Cole", "Petra Wall",
						  "Tyriq Woodley", "Jarvis Joyner", "Cora Povey", "Xena Wyatt",
						  "Marsha Milner", "Ramone Chavez", "Max Myers", "Kali Hayward",
						  "Ava Mason", "Jia Simmons", "Rehan Rahman", "Bea Austin", "Zeshan Brandt",
						  "Blade Kouma", "Ziggy Tillman", "Matias Blaese", "Melina Cartwright",
						  "Enid Blankenship", "Izabella Owen", "Winston Cain", "Emile Mccarthy",
						  "Lorcan Gaines", "Kady Pollard", "Ksawery Zimmerman", "Jon-Paul Kelley",
						  "Hadassah Ortiz", "Alysia Fisher", "Claude Mcfarlane", "Alexis Pratt",
						  "Forrest Weber", "Miguel Carty", "Demi Allman", "Rukhsar Carver",
						  "Troy Puckett", "Santiago Hendrix", "Debra Edmonds", "Tiya Miller",
						  "Kelsey Tran", "Tymon Coleman", "Tayla Weiss", "Meredith Harwood",
						  "Abi Parsons", "Sanya Porter", "Tarun Frank", "Ty Grey", "Alima Mcdonald",
						  "Gabrielius Odonnell", "Louise Carson", "Reuben Tate", "Cieran Schofield",
						  "Safa Reed", "Diesel Gay", "Korban Hurst", "Griff Rose", "Leela Brett",
						  "Rebecca Ayala", "Karl Mccaffrey", "Lowri Bateman", "Gracie-Leigh Huff",
						  "Alishia Reeve", "Raisa Dawson", "Vihaan Povey", "Hareem Adamson",
						  "Leigha Lin", "Fariha Chen", "Alan Naylor", "Amiee Kumar", "Sami Fry",
						  "Carlos York", "Kelsi Roberts", "Suhayb Banks", "Ryker Morton",
						  "Hywel Robinson", "Reis Aldred", "Abbas Gough", "Nuha Boyd",
						  "Ruqayyah Hudson", "Ameena Morrow", "Emilio Orr", "Hubert Rush",
						  "Willem Reilly", "Manisha Petty", "Tj Lennon", "Harris Sawyer",
						  "Lois Petersen", "Rui Shea", "Mikolaj Rios", "Ed Fitzgerald", "Jax Nava",
						  "Idrees Mays", "Chelsey Reeves", "Alec Rowley", "Elissa Stone",
						  "Jeffrey Elliott", "Giovanni Iles", "Cairo Whyte", "Reiss Haney",
						  "Camille Feeney", "Adeline Robles", "Anjali Barnett", "Finnlay Lucero",
						  "Oisin Lawrence", "Tea Emerson", "Ariya Wise", "Alina Espinoza",
						  "Aniyah Humphreys", "Eadie Rosales", "Eilidh Buchanan", "Maeve Davenport",
						  "Matthew Hensley", "Albert Simon", "Isra Juarez", "Borys Corona",
						  "Arnas Waller", "Arun Whitworth", "Mariyam Sparrow", "Serenity Jacobs",
						  "Caleb Dejesus", "Ciaran Baldwin", "Ezekiel Ireland", "Callan Jordan",
						  "Sabiha Akhtar", "Marjorie Liu", "Franklyn Downs", "Wesley Lacey",
						  "Kamila Read", "Nina Booker", "Rafi Bradley", "Hafsah Kelley",
						  "Chanelle Espinosa", "Dayna Morrow", "Gage Greene", "Said Penn",
						  "Sheikh Hunter", "Zack Cabrera", "Braydon Montgomery", "Joan Rees",
						  "Yannis Byers", "Sue Farrell", "Adeeb Hayes", "Aviana Walters",
						  "Parris Blanchard", "Sahib Lara", "Chandler Mccormick", "Sofie Sutton",
						  "Skylar Dunkley", "Isla-Rae Alford", "Alejandro Mcgee", "Iwan Wade",
						  "Wilf Solis", "Bonita Rangel", "Mackenzie Leech", "Thomas Gunn",
						  "Maisie Rennie", "Areebah Alexander", "Alyce Willis", "Vishal Whittaker",
						  "Zion Warner", "Misty Hamer", "Osman Delaney", "Evalyn York",
						  "Mack Bartlett", "Harvir Ferry", "Aya Lennon", "Xena Greer",
						  "Becky Herrera", "Jamelia Atkins", "Maddie Cruz", "Patryk Lambert",
						  "Joy Garza", "Jimi Valenzuela", "Kelan Raymond", "Rikki Preece",
						  "Jordan Travis", "Katie Cole", "Kara Mullins", "Mared Hutton",
						  "Azeem Clemons", "Vikram Schwartz", "Hamza Holden", "Kallum Lyon",
						  "Aiyla Avila", "Matthias Pitt", "Elsie-May Sosa", "Veer Alvarez",
						  "Kai Bateman", "Alessia Searle", "Rabia Cottrell", "Jemimah Vickers",
						  "Katie-Louise Compton", "Florrie Barrow", "Hawwa Bonilla",
						  "Eleasha Baker", "Lyla Shannon", "Kirstie Schneider", "Faye Christensen",
						  "Kieran Blackburn", "Sanjeev Amos", "Vlad Ramirez", "Horace Burns",
						  "Bobby Gibson", "Esa Lawrence", "Sahil Mckay", "Samina Alcock",
						  "Shiloh Wagstaff", "Carolyn Brock", "Dion Hamilton", "Elif Lopez",
						  "Cadi Whitmore", "Imani Marriott", "Fannie Andrade", "Alysia Santiago",
						  "Tracey Mooney", "Nikodem Busby", "Jenny Merrill", "Anabella Mcfarland",
						  "Waleed Wickens", "Antoni Robbins", "Hanna Huang", "Fleur Gibbs",
						  "Kuba Charles", "Jed Espinoza", "Kay Ryan", "Hamaad Chambers",
						  "Alayna Curry", "Conor Kline", "Jokubas Kirby", "Dolores Beck",
						  "Carla Simon", "Mali Bernard", "Nur Pena", "Amar Pace", "Leah Dickerson",
						  "Alasdair Lowery", "Vernon Kaur", "Chloe-Louise Guy", "Avani Knowles",
						  "Kiaan Le", "Kelsey Davie", "James Murillo", "Jerry Carney", "Amba Craig",
						  "Amaya Flores", "Akbar Hansen", "Daryl Warren", "Riaan Connelly",
						  "Ashlee Trujillo", "Muskaan Coates", "Samir Duffy", "Nikolas Lozano",
						  "Ewan Hampton", "Tobey Gaines", "Conall Lambert", "Nafeesa Freeman",
						  "Summer-Rose Dodson", "Sorcha Mcmahon", "Aqib Dean", "Arley Blackmore",
						  "Mercedes Welch", "Abid Bean", "Kasim Blackwell", "Teddie Garza",
						  "Alexie Reader", "Monika Tillman", "Arnold Bellamy", "Jose Rahman",
						  "Josie Paul", "Brett Pate", "Bailey Branch", "Donna Robles",
						  "Vincenzo Burch", "Savanna Jimenez", "Arbaaz Guerra", "Arman Anthony",
						  "Osman Duggan", "Olivia-Grace Johns", "Evelina Paine", "Kiah Miller",
						  "Abdurahman Read", "Lyla Ayala", "Winston Munro", "Shelbie Daugherty",
						  "Romy Coulson", "Wasim Lewis", "Esa Bush", "Leonardo Chan",
						  "Roksana Wade", "Otis Crouch", "Poppie Michael", "Isla Harvey",
						  "Kirstin Halliday", "Corbin Baird", "Clive Watkins", "Lynden Oneil",
						  "Izabelle Clarkson", "Toni Mckay", "Melina Steadman", "Jamil Hester",
						  "Kien Mueller", "Eryn Levine", "Jena Healy", "Lacie Mclaughlin",
						  "Caio Lang", "Eleni Mercado", "Keely Fulton", "Rhonda Xiong",
						  "Sukhmani Nielsen", "Kaine Mcneill", "Jun Long", "Mikey Weston",
						  "Mylah Avery", "Tilly Glass", "Iman Ireland", "Harvey Rossi",
						  "Kenneth Wilkes", "Israr Hobbs", "Ryan Hess", "Inaaya Webber",
						  "Kendall Galvan", "Jaylan Mccartney", "Emil Maxwell", "Heidi Swift",
						  "Ophelia Booth"};

static int grades2[] = {7, 49, 73, 58, 30, 72, 44, 78, 23, 9, 40, 65, 92, 42, 87, 3, 27, 29, 40,
						12, 3, 69, 9, 57, 60, 33, 99, 78, 16, 35, 97, 26, 12, 67, 10, 33, 79, 49,
						79, 21, 67, 72, 93, 36, 85, 45, 28, 91, 94, 57, 1, 53, 8, 44, 68, 90, 24,
						96, 30, 3, 22, 66, 49, 24, 1, 53, 77, 8, 28, 33, 98, 81, 35, 13, 65, 14,
						63, 36, 25, 69, 15, 94, 29, 1, 17, 95, 5, 4, 51, 98, 88, 23, 5, 82, 52,
						66, 16, 37, 38, 44, 1, 97, 71, 28, 37, 58, 77, 97, 94, 4, 9, 31, 45, 75,
						35, 98, 42, 99, 68, 12, 60, 57, 94, 8, 95, 68, 13, 30, 6, 62, 42, 65, 82,
						52, 67, 21, 95, 12, 71, 1, 90, 31, 38, 57, 16, 90, 40, 79, 35, 6, 72, 98,
						95, 19, 54, 23, 89, 60, 5, 26, 23, 6, 13, 70, 38, 94, 20, 44, 66, 34, 26,
						94, 63, 38, 44, 90, 50, 59, 23, 47, 85, 17, 72, 39, 47, 85, 96, 85, 23,
						20, 44, 68, 35, 15, 25, 34, 42, 11, 79, 52, 44, 95, 18, 96, 92, 15, 91,
						33, 69, 97, 53, 47, 25, 10, 62, 11, 8, 77, 61, 25, 35, 68, 95, 76, 67,
						39, 74, 31, 56, 1, 72, 60, 94, 84, 55, 89, 7, 15, 93, 69, 80, 55, 55, 6,
						63, 2, 76, 8, 49, 31, 44, 38, 8, 97, 51, 49, 3, 31, 31, 14, 19, 75, 9,
						80, 29, 23, 54, 60, 37, 45, 17, 25, 0, 56, 64, 97, 48, 4, 50, 50, 76, 12,
						54, 97, 4, 81, 48, 65, 78, 99, 9, 29, 53, 83, 47, 7, 73, 22, 5, 76, 53,
						24, 30, 66, 0, 44, 70, 85, 16, 98, 55, 33, 57, 76, 78, 66, 57, 11, 78,
						14, 19, 37, 33, 91, 20, 62, 33, 97, 31, 88, 89, 73, 77, 4, 58, 0, 54, 60,
						15, 47, 80, 30, 55, 46, 7, 38, 0, 26, 35, 57, 13, 14, 93, 60, 54, 18, 57,
						85, 29, 15, 63, 2, 17, 43, 19, 67, 47, 69, 95, 3, 73, 3, 48, 85, 58, 59,
						6, 30, 24, 32, 73, 3, 97, 20, 50, 31, 80, 3, 0, 20, 33, 58, 3, 76, 50,
						34, 80, 79, 32, 74, 49, 42, 49, 71, 10, 79, 83, 70, 40, 23, 50, 71, 29,
						18, 46, 99, 30, 21, 76, 24, 44, 58, 96, 71, 64, 60, 98, 51, 40, 3, 51, 1,
						5, 80, 18, 74, 49, 13, 20, 25, 12, 83, 88, 17, 8, 50, 24, 95, 57, 11, 90,
						66, 10, 93, 53, 65, 60, 42, 3, 52, 7, 41, 10, 0, 99, 27, 71, 87, 14, 25,
						41, 17, 48, 42, 15, 74, 45, 73, 20, 11, 39, 54, 5, 29, 53, 89, 66, 56, 4,
						60, 98, 92, 20, 16, 80, 67, 52, 39, 98};

int main(int argc, const char *argv[])
{
	std::chrono::steady_clock sc;
	auto start = sc.now();

	VLVector<Student, STATIC_CAPACITY> Students;


	for (int i = 0; i < 100; i++)
	{
		Student s = Student(names2[i], grades2[i]);
		Students.push_back(s);
	}

	VLVector<Student, STATIC_CAPACITY>::iterator j;

	VLVector<Student, STATIC_CAPACITY>::iterator begin = Students.begin();
	VLVector<Student, STATIC_CAPACITY>::iterator end = Students.end();

	Student s1 = {"Putta", 65};
	Student s2 = {"Hezzy", 94};

	VLVector<Student, STATIC_CAPACITY>::iterator sp1 = &Students[15];
	VLVector<Student, STATIC_CAPACITY>::iterator sp2 = &Students[20];

	Students.insert(sp1, s1);
	Students.insert(sp2, s2);

	cout << "---------------------------------" << endl;
	end = Students.end();
	int i = 1;
	for (VLVector<Student, STATIC_CAPACITY>::iterator it = begin; it <= end; it++)
	{
		cout << i << " " << *it << endl;
		i = i + 1;
	}

	auto etime = sc.now();
	auto time_span = static_cast<std::chrono::duration<double>>(etime - start);   // measure time
	// span between start & end
	cout << "Operation took: " << time_span.count() << " seconds !!!";
	return EXIT_SUCCESS;
}