

#ifndef STR_MANIP_UTILS_H
#define STR_MANIP_UTILS_H 


using namespace std;


string str_to_lower(string s) {
    string sl="";
    for(int i = 0; i < s.length(); i++){
        sl+=tolower(s[i]);
    }
    return sl;
}

bool check_input_option(string input, string opt) {
    opt = str_to_lower(opt);
    input = str_to_lower(input);
    return input==opt || input == "("+opt+")" ;
}

int substr_pos(string text, string subs) {
	int pos = text.find(subs);
	return pos==string::npos? -1: pos;
}


bool is_substr(string text, string subs) {
	return substr_pos(text,subs)>=0;
}

string str_to_upper(string s) {
    string sl="";
    for(int i = 0; i < s.length(); i++){
        sl+=toupper(s[i]);
    }
    return sl;
}



string simplify_pattern(string pattern) {
    // consecutive occurences of '*' can be replaced with a single '*'.
    char last='\0', last2='\0';
    string reduced = "";
    for(char curr:pattern) {
        if (curr != '*' || last != '*' || last2=='\\') {
            reduced+=curr;
        }
        last2=last;
        last=curr;
    }
    return reduced;
}

// assume mtach must be full text.
// for wildcard, 
//    '*' matches any sequence of chars, inculing empty string.
//    '?' matches any one char.
// '\?', '\*' can escape them.
// '\\' would be '\'


bool wildcard_match(string text, string pattern, bool is_simple=false) {
    if (!is_simple)
        pattern = simplify_pattern(pattern);
    if (text=="") {
        return pattern == "" || pattern=="*";
    }
    int ti=0,pi=0;
    bool escaped = false;
    while (ti<text.length() && pi<pattern.length()) {
        if (escaped || !(pattern[pi]=='\\' || pattern[pi]=='*'
                         ||pattern[pi]=='?')) {

            if (text[ti]!=pattern[pi]) {
                return false;
            }
            escaped= false;
        }else if (pattern[pi]=='?') {
            // no checks needed
        }else if (pattern[pi]=='\\') {
            escaped = true;
            ti--;
        }else {
            // the unescaped * case.
            // This will be inefficient since arrays are not allowed.
            /**/
            if (pi+1==pattern.length()) {
                return true;
            }
            string subpattern = pattern.substr(pi+1);
            //cout <<"...: "<< subpattern <<endl;
            if (subpattern=="\\") {
                return false;
            }
            string subtext = text.substr(pi);

            string prefix (1,subpattern[0]=='\\'? subpattern[1]: subpattern[0]);

            subpattern= subpattern.substr(subpattern[0]=='\\'? 2:1);

            for (char c: subpattern) {
                if (c=='\\'||c=='*'||c=='?') {
                    break;
                }
                prefix+=(c);
            }

            int pos;
            while ((pos=substr_pos(subtext,prefix))>=0) {
                subtext = subtext.substr(pos+1);
                if (wildcard_match(subtext, subpattern, true)) {
                    return true;
                }
            }
            return false;
        }
        ti++;pi++;
    }
    return ti==text.length() && pi==pattern.length();
}

#endif

