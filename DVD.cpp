/*
 * DVD.cpp
 *
 *  Created on: Oct 21, 2020
 *      Author: Dinesh Angadipeta DXA@190032
 */

#include "DVD.h"

DVD::DVD() {
	// TODO Auto-generated constructor stub
	title = "";
	available = 0;
	rented = 0;

}

DVD::~DVD() {
	// TODO Auto-generated destructor stub
}


bool DVD::operator<(const DVD &rhs)
{
    return title < rhs.title;
}

bool DVD::operator<(const string &rhs)
{
    return title < rhs;
}

bool DVD::operator>(const DVD &rhs)
{
    return title > rhs.title;
}

bool DVD::operator>(const string &rhs)
{
    return title > rhs;
}

bool DVD::operator==(const DVD &rhs)
{
    return title == rhs.title;
}

bool DVD::operator==(const string &rhs)
{
    return title == rhs;
}


