#include "config.hpp"
#include <nds/system.h>

#include "json.hpp"
#include "flashcard.hpp"
#include "lang.hpp"

nlohmann::json configJson;

Lang::Language sysLang() {
	switch(PersonalData->language) {
		case 0:
			return Lang::jp;
		case 1:
		default:
			return Lang::en;
		case 2:
			return Lang::fr;
		case 3:
			return Lang::de;
		case 4:
			return Lang::es;
	}
}

void Config::load() {
	FILE* file = fopen(sdFound() ? "sd:/_nds/pkmn-chest/config.json" : "fat:/_nds/pkmn-chest/config.json", "r");
	if(file) {
		configJson = nlohmann::json::parse(file, nullptr, false);
		fclose(file);
	}
}

void Config::save() {
	FILE* file = fopen(sdFound() ? "sd:/_nds/pkmn-chest/config.json" : "fat:/_nds/pkmn-chest/config.json", "w");
	if(file) {
		fwrite(configJson.dump(1, '\t').c_str(), 1, configJson.dump(1, '\t').size(), file);
		fclose(file);
	}
}

bool Config::getBool(const std::string &key) {
	if(!configJson.contains(key)) {
		return false;
	}
	return configJson.at(key).get_ref<const bool&>();
}
void Config::setBool(const std::string &key, bool v) {
	configJson[key] = v;
}

int Config::getInt(const std::string &key) {
	if(!configJson.contains(key)) {
		return 0;
	}
	return configJson.at(key).get_ref<const int64_t&>();
}
void Config::setInt(const std::string &key, int v) {
	configJson[key] = v;
}

std::string Config::getString(const std::string &key) {
	if(!configJson.contains(key)) {
		return "";
	}
	return configJson.at(key).get_ref<const std::string&>();
}
void Config::setString(const std::string &key, const std::string &v) {
	configJson[key] = v;
}

int Config::getLang(const std::string &key) {
	if(!configJson.contains(key)) {
		return sysLang();
	}
	return configJson.at(key).get_ref<const int64_t&>();
}
