#include <bitset>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <array>

std::bitset<8> hexStringToBitset(char a, char b){
  std::bitset<8> bits1;
  std::bitset<8> bits2;
  switch (a) {
    case '0': bits1 = std::bitset<8>{0b0000'0000}; break;
    case '1': bits1 = std::bitset<8>{0b0001'0000}; break;
    case '2': bits1 = std::bitset<8>{0b0010'0000}; break;
    case '3': bits1 = std::bitset<8>{0b0011'0000}; break;
    case '4': bits1 = std::bitset<8>{0b0100'0000}; break;
    case '5': bits1 = std::bitset<8>{0b0101'0000}; break;
    case '6': bits1 = std::bitset<8>{0b0110'0000}; break;
    case '7': bits1 = std::bitset<8>{0b0111'0000}; break;
    case '8': bits1 = std::bitset<8>{0b1000'0000}; break;
    case '9': bits1 = std::bitset<8>{0b1001'0000}; break;
    case 'A': bits1 = std::bitset<8>{0b1010'0000}; break;
    case 'B': bits1 = std::bitset<8>{0b1011'0000}; break;
    case 'C': bits1 = std::bitset<8>{0b1100'0000}; break;
    case 'D': bits1 = std::bitset<8>{0b1101'0000}; break;
    case 'E': bits1 = std::bitset<8>{0b1110'0000}; break;
    case 'F': bits1 = std::bitset<8>{0b1111'0000}; break;
  }
  switch (b) {
    case '0': bits2 = std::bitset<8>{0b0000'0000}; break;
    case '1': bits2 = std::bitset<8>{0b0000'0001}; break;
    case '2': bits2 = std::bitset<8>{0b0000'0010}; break;
    case '3': bits2 = std::bitset<8>{0b0000'0011}; break;
    case '4': bits2 = std::bitset<8>{0b0000'0100}; break;
    case '5': bits2 = std::bitset<8>{0b0000'0101}; break;
    case '6': bits2 = std::bitset<8>{0b0000'0110}; break;
    case '7': bits2 = std::bitset<8>{0b0000'0111}; break;
    case '8': bits2 = std::bitset<8>{0b0000'1000}; break;
    case '9': bits2 = std::bitset<8>{0b0000'1001}; break;
    case 'A': bits2 = std::bitset<8>{0b0000'1010}; break;
    case 'B': bits2 = std::bitset<8>{0b0000'1011}; break;
    case 'C': bits2 = std::bitset<8>{0b0000'1100}; break;
    case 'D': bits2 = std::bitset<8>{0b0000'1101}; break;
    case 'E': bits2 = std::bitset<8>{0b0000'1110}; break;
    case 'F': bits2 = std::bitset<8>{0b0000'1111}; break;
  }

  return bits1 | bits2;
}

std::string intToString(int a){
  switch (a) {
    case 10: return "A";
    case 11: return "B";
    case 12: return "C";
    case 13: return "D";
    case 14: return "E";
    case 15: return "F";
    default: return std::to_string(a);
  }
}

std::string makeColorTable(int r, int g, int bl){
  std::string a;
  std::string b;
  a = intToString(r/16);
  b = intToString(r%16);
  
  std::string c = intToString(g/16);
  std::string d = intToString(g%16);

  std::string e = intToString(bl/16);
  std::string f = intToString(bl%16);
  
  return e + f + " " + c + d + " " + a + b + " ";
  // return "0" + std::to_string(r) + " 0" + std::to_string(g) + " 0" + std::to_string(b) + " ";
}

std::string makeByteArr(int i){
  std::string a = intToString((i/16)%16);
  std::string b = intToString(i%16);
  std::string c = intToString((i/16/16/16)%16);
  std::string d = intToString((i/16/16)%16);
  std::string e = intToString((i/16/16/16/16/16)%16);
  std::string f = intToString((i/16/16/16/16)%16);
  std::string g = intToString((i/16/16/16/16/16/16/16)%16);
  std::string h = intToString((i/16/16/16/16/16/16)%16);
  return a + b + " " + c + d + " " + e + f + " " + g + h + " ";
}

std::string getHeaderString(int w, int h){
  std::string h1 = "42 4D ";
  std::string h2 = makeByteArr(54 + 3*h*w);
  std::string h3 = "00 00 00 00 36 00 00 00 28 00 00 00 ";
  std::string h4 = makeByteArr(w);
  std::string h5 = makeByteArr(h);
  std::string h6 = "01 00 18 00 00 00 00 00 ";
  std::string h7 = makeByteArr(3 * h * w);
  std::string h8 = "13 0B 00 00 13 0B 00 00 00 00 00 00 00 00 00 00 ";
  std::string s = h1 + h2 + h3 + h4 + h5 + h6 + h7 + h8;
  return s;
  
}

int main(){
  std::ifstream inFile("res/example.ppm");
  std::ofstream outFile("res/out.bmp", std::ofstream::binary);
  int width = 256;
  int height = 256;

  std::string newLine;
  int i {0};
  std::string str = "";
  std::string headStr;
  
  while (getline (inFile, newLine)) {
    // Output the text from the file
    if (i < 3){
      std::cout << newLine << "\n";
    }

    if (i == 1){
      std::string wText = newLine.substr(0, 3);
      std::string hText = newLine.substr(4, 3);
      width = stoi(wText);
      height = stoi(hText);
      headStr = getHeaderString(width, height);
    }

    if (i > 2){
      std::stringstream ss (newLine);
      std::array<int, 3> rgb;
      int j = 0;
      int num;
      while (ss >> num){
        rgb[j] = num;
        j++;
      }
      str.insert(0, makeColorTable(rgb[0], rgb[1], rgb[2]));
    }
    i++;
  }

  headStr.append(str);
  
  for (int i = 0; i < headStr.length(); i += 3){
    std::bitset<8> byte = hexStringToBitset(headStr[i], headStr[i+1]);
    outFile << std::hex << static_cast<char>(byte.to_ulong());
  }
  
  
  return 0;
  
} 
