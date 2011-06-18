/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef ABOUT_H_INCLUDED
#define ABOUT_H_INCLUDED

#include <string>

/*"About" information is divided into different levels:
    L0 = standard text, pre-defined and not changeable
    L1 = basic information, only set by user
    L2 = advanced information, can be generated automatically by L0/L1 information but can be also set manually by user
    L3 = advanced information, generated automatically by L0/L1/L2 information

  * = information that must be set by user to get a proper result
*/

class About
{
    public:
        enum License
        {
            LICENSE_GPL,
            LICENSE_ALL_RIGHTS_RESERVED,
            LICENSE_NONE
        };

    private:
        //*** static members: "standard text" that is used to generate "About" text ***
        //copyright: <pre_copyright_1><copyright_year><pre_copyright_2><copyright_author>
        static const std::string pre_copyright_1;
        static const std::string pre_copyright_2;
        //license: array with texts for pre-defined licenses, index defined by enum 'License': string for license "X" is 'linceses[LICENSE_X]'
        static const std::string licenses[];

    public:
        About();
        About(std::string name, std::string version="", std::string author="", std::string copyright_year="", License license=LICENSE_NONE); //set most common information and call 'generate()' and 'update()'
    public:
        //"About" information
        std::string name; //L1*
        std::string author; //L1
        std::string version; //L1
        std::string date; //L1
        std::string description; //L1
        std::string copyright_year; //L2
        std::string copyright_author; //L2
        std::string copyright; //L2
        std::string license; //L2

        std::string about; //L3 resulting "About" text
    public:
        //set methods
        void set_name(std::string name);
        void set_description(std::string description);
        void set_version(std::string version);
        void set_copyright(std::string copyright);
        void set_license(std::string license);
        void set_license(License license);

        void generate(bool f = false); //generate L2/L3 information that are not yet set (or overwrites them if 'f==true')
        void update(); //generate 'about' by flicking given information together

        //get methods
        std::string get_about() const;

        friend std::ostream& operator<<(std::ostream& os, const About& a); //add "About" text to 'os'
};


#endif // ABOUT_H_INCLUDED
