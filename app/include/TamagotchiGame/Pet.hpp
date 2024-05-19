#include <string>

class Pet {
	public:
		Pet();

		void Feed(const std::string& what);

		void RetrieveStats();

		void UpdateStats();

		static int GetStat(const std::string&);
		
		static void SetStat(const std::string&, int);
		//void Poop();

		//void Play();
	private:
		static std::map<std::string, int> fields_;
};
