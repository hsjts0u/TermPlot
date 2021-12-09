#pragma once

#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <cwchar>
#include <float.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string.h>

const char *const styles[][11] = {
    {"-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"}, //ASCII
	{"—", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"}, //Basic
	{"─", "│", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"}, //Light
	{"━", "┃", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"}, //Heavy
	{"═", "║", "╔", "╦", "╗", "╠", "╬", "╣", "╚", "╩", "╝"}, //Double
	{"╌", "╎", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"}, //Light Dashed
	{"╍", "╏", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"}	 //Heavy Dashed
};

const char *const colors[] = {"\e[39m", "\e[30m", "\e[31m", "\e[32m", "\e[33m", "\e[34m", "\e[35m", "\e[36m", "\e[37m", "\e[90m", "\e[91m", "\e[92m", "\e[93m", "\e[94m", "\e[95m", "\e[96m", "\e[97m"};

const char *const dots[] = {"⠀", "⠁", "⠂", "⠃", "⠄", "⠅", "⠆", "⠇", "⠈", "⠉", "⠊", "⠋", "⠌", "⠍", "⠎", "⠏", "⠐", "⠑", "⠒", "⠓", "⠔", "⠕", "⠖", "⠗", "⠘", "⠙", "⠚", "⠛", "⠜", "⠝", "⠞", "⠟", "⠠", "⠡", "⠢", "⠣", "⠤", "⠥", "⠦", "⠧", "⠨", "⠩", "⠪", "⠫", "⠬", "⠭", "⠮", "⠯", "⠰", "⠱", "⠲", "⠳", "⠴", "⠵", "⠶", "⠷", "⠸", "⠹", "⠺", "⠻", "⠼", "⠽", "⠾", "⠿", "⡀", "⡁", "⡂", "⡃", "⡄", "⡅", "⡆", "⡇", "⡈", "⡉", "⡊", "⡋", "⡌", "⡍", "⡎", "⡏", "⡐", "⡑", "⡒", "⡓", "⡔", "⡕", "⡖", "⡗", "⡘", "⡙", "⡚", "⡛", "⡜", "⡝", "⡞", "⡟", "⡠", "⡡", "⡢", "⡣", "⡤", "⡥", "⡦", "⡧", "⡨", "⡩", "⡪", "⡫", "⡬", "⡭", "⡮", "⡯", "⡰", "⡱", "⡲", "⡳", "⡴", "⡵", "⡶", "⡷", "⡸", "⡹", "⡺", "⡻", "⡼", "⡽", "⡾", "⡿", "⢀", "⢁", "⢂", "⢃", "⢄", "⢅", "⢆", "⢇", "⢈", "⢉", "⢊", "⢋", "⢌", "⢍", "⢎", "⢏", "⢐", "⢑", "⢒", "⢓", "⢔", "⢕", "⢖", "⢗", "⢘", "⢙", "⢚", "⢛", "⢜", "⢝", "⢞", "⢟", "⢠", "⢡", "⢢", "⢣", "⢤", "⢥", "⢦", "⢧", "⢨", "⢩", "⢪", "⢫", "⢬", "⢭", "⢮", "⢯", "⢰", "⢱", "⢲", "⢳", "⢴", "⢵", "⢶", "⢷", "⢸", "⢹", "⢺", "⢻", "⢼", "⢽", "⢾", "⢿", "⣀", "⣁", "⣂", "⣃", "⣄", "⣅", "⣆", "⣇", "⣈", "⣉", "⣊", "⣋", "⣌", "⣍", "⣎", "⣏", "⣐", "⣑", "⣒", "⣓", "⣔", "⣕", "⣖", "⣗", "⣘", "⣙", "⣚", "⣛", "⣜", "⣝", "⣞", "⣟", "⣠", "⣡", "⣢", "⣣", "⣤", "⣥", "⣦", "⣧", "⣨", "⣩", "⣪", "⣫", "⣬", "⣭", "⣮", "⣯", "⣰", "⣱", "⣲", "⣳", "⣴", "⣵", "⣶", "⣷", "⣸", "⣹", "⣺", "⣻", "⣼", "⣽", "⣾", "⣿"};

const int values[][4] = {{0x1, 0x2, 0x4, 0x40}, {0x8, 0x10, 0x20, 0x80}};

const char *const fractions[] = {"¼", "½", "¾", "⅐", "⅑", "⅒", "⅓", "⅔", "⅕", "⅖", "⅗", "⅘", "⅙", "⅚", "⅛", "⅜", "⅝", "⅞"};

const long double fractionvalues[] = {1.0L / 4.0L, 1.0L / 2.0L, 3.0L / 4.0L, 1.0L / 7.0L, 1.0L / 9.0L, 1.0L / 10.0L, 1.0L / 3.0L, 2.0L / 3.0L, 1.0L / 5.0L, 2.0L / 5.0L, 3.0L / 5.0L, 4.0L / 5.0L, 1.0L / 6.0L, 5.0L / 6.0L, 1.0L / 8.0L, 3.0L / 8.0L, 5.0L / 8.0L, 7.0L / 8.0L};

typedef struct graphoptions
{

    bool border = true;
    bool axislabel = true;
    bool axisunitslabel = true;
    char *title = nullptr;
    unsigned int style = 2;
    unsigned int color = 2;
    graphoptions(void) = default;
    ~graphoptions(void) = default;

} graphoptions;

const graphoptions graphoptionsdefault;

inline int strcol(const char *const str)
{
    
    size_t length = strlen(str);
    for (size_t i=0; i < length; i++) 
    {
        if (std::iscntrl(str[i])) 
        {
            std::cerr << "\nError. Control character in string.\n";
            std::cout << "Control character: " << (int)str[i] << "\n";
        }
    }

    length = mbstowcs(NULL, str, 0);
    if (length == (size_t)-1)
    {
        std::cerr << "\nError! mbstowcs failed. Invalid multibyte chracter.\n";
        exit(1);
    }
    ++length;

    wchar_t *wcstring = new wchar_t[length];
    if (mbstowcs(wcstring, str, length) == (size_t)-1)
    {
        if (wcstring != NULL) delete [] wcstring;

        std::cerr << "\nError. mbstowcs failed. Invalid multibyte character.\n";
        exit(1);
    }
    
    int width = wcswidth(wcstring, length);
    if (width == -1) 
    {
        std::cerr << "\nError! wcswidth failed. Nonprintable wide character.\n";
		exit(1);
    }

    if (wcstring != NULL) delete [] wcstring;

    return width;

}

inline std::string wrap(const char *const str, const std::size_t line_length)
{

    char words[strlen(str) + 1];
    strcpy(words, str);
    std::string wrapped;
    size_t index = 0;
    size_t linelen = 0;

    while (words[index] != '\0') 
    {
        if (words[index] == '\n')
		{
			linelen = 0;
		} 
        else if (isspace(words[index]))
		{
			size_t tempindex = index + 1;
			size_t templinelen = linelen;
			while (!isspace(words[tempindex]) and words[tempindex] != '\0')
			{
				++templinelen;
				++tempindex;
			}

			char temp[templinelen + 1];
			strncpy(temp, words + (index - linelen), templinelen);
			temp[templinelen] = '\0';

			size_t width = strcol(temp);
			if (width >= line_length)
			{
				words[index] = '\n';
				linelen = 0;
			}
		}

		if (words[index] == '\t') linelen += 8 - (linelen % 8);
		else if (words[index] != '\n') ++linelen;
		++index;
    }
    
    wrapped = words;
    return wrapped;

}

inline std::size_t outputlabel(const long double label, std::ostringstream &strm)
{
    
    bool output = false;
	long double intpart = 0;
	long double fractionpart = abs(modf(label, &intpart));

	for (unsigned int i = 0; i < (sizeof fractions / sizeof fractions[0]) and !output; ++i)
	{
		if (abs(fractionpart - fractionvalues[i]) < DBL_EPSILON)
		{
			if (intpart != 0) strm << intpart;
			strm << fractions[i];
			output = true;
		}
	}

	if (abs(label) >= DBL_EPSILON)
	{
		if (!output and fmod(label, M_PI) == 0)
		{
			const char symbol[] = "π";
			intpart = label / M_PI;

			if (intpart == -1) strm << "-";
			else if (intpart != 1) strm << intpart;

			strm << symbol;
			output = true;
		}
		else if (!output and fmod(label, M_E) == 0)
		{
			const char symbol[] = "e";
			intpart = label / M_E;

			if (intpart == -1) strm << "-";
			else if (intpart != 1)strm << intpart;

			strm << symbol;
			output = true;
		}
	}

	if (!output) strm << label;
	size_t length = strcol(strm.str().c_str());

    return length;

}