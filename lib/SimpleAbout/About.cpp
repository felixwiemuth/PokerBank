/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#include "About.h"
#include <sstream>

using namespace std;

const string About::pre_copyright_1 = "Copyright (C)";
const string About::pre_copyright_2 = " by ";
const string About::licenses[] = {  "Licensed under the GNU GENERAL PUBLIC LICENSE\nhttp://www.gnu.org/licenses/gpl.txt",
                                    "All rights reserved.",
                                    ""  };

About::About()
{

}

About::About(string name, string version, string author, string copyright_year, License license) : name(name), version(version), author(author), copyright_year(copyright_year), license(licenses[license])
{
    generate();
    update();
}

void About::set_name(string name)
{
    this->name = name;
}
void About::set_description(string description)
{
    this->description = description;
}
void About::set_version(string version)
{
    this->version = version;
}
void About::set_copyright(string copyright)
{
    this->copyright = copyright;
}
void About::set_license(string license)
{
    this->license = license;
}

void About::set_license(License license)
{
    this->license = licenses[license];
}

void About::generate(bool f)
{
    //L2
    if (f || copyright_year.empty())
        copyright_year = date;
    if (f || copyright_author.empty())
        copyright_author = author;
    if (f || copyright.empty())
    {
        copyright = pre_copyright_1;
        if (!copyright_year.empty())
            copyright += " " + copyright_year;
        if (!copyright_author.empty())
            copyright += pre_copyright_2 + copyright_author;
    }
}

void About::update()
{
    ostringstream os;

    if (!name.empty())
    {
        os << name;
        if (!version.empty())
            os << " " << version;
    }
    if (!description.empty())
        os << "\n" << description;
    if (!copyright.empty())
        os << "\n" << copyright;
    if (!license.empty())
        os << "\n" << license;

    about = os.str();
}

string About::get_about() const
{
    return about;
}

ostream& operator<<(ostream& os, const About& a)
{
    os << a.about;
    return os;
}
