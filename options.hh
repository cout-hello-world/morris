#ifndef OPTIONS_HH
#define OPTIONS_HH
#include <vector>
class options {
	class option {
		std::string name;
		char char_name;
		std::string help;
		std::string default_value;
	};

	void add_option(const option &opt)
	{
		opts.push_back(opt);
	}

	void process_cmds(const char *const *argv, int argc)
	{
		// search through and assign as appropriate
	}
private:
	std::vector<option> opts;
};

#endif
