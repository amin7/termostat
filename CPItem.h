/*
 * CPItem.h
 *
 *  Created on: 9 ????. 2018 ?.
 *      Author: User
 */

#ifndef CPITEM_H_
#define CPITEM_H_

#include <ArduinoJson.h>//https://github.com/bblanchon/ArduinoJson.git
//https://arduinojson.org

class CPItem {
private:
public:
  virtual bool deSerialize(const JsonObject& root)=0;
  virtual bool serialize(JsonObject& root) const=0;
};


#endif /* CPITEM_H_ */
