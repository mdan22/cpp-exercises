#include <iostream>
#include <bitset>
#include <cstdint>
#include <random>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

union FloatBits {
    float f;
    uint32_t bits;
};

string formatIEEE(uint32_t bits) {
    string binary = bitset<32>(bits).to_string();
    return binary.substr(0,1) + " " + 
           binary.substr(1,4) + " " + 
           binary.substr(5,4) + " " + 
           binary.substr(9,4) + " " + 
           binary.substr(13,4) + " " + 
           binary.substr(17,4) + " " + 
           binary.substr(21,4) + " " + 
           binary.substr(25,4) + " " + 
           binary.substr(29,3);
}

void showIEEESteps(float num) {
    FloatBits fb{num};
    
    cout << "\n=== Detaillierte IEEE-754 Analyse ===\n";
    cout << "Eingabezahl: " << num << "\n";
    cout << "IEEE-754 Format: " << formatIEEE(fb.bits) << "\n";

    // Vorzeichen
    cout << "\nSchritt 1 - Vorzeichen:\n";
    bool isNegative = fb.bits >> 31;
    cout << "Bit 31 = " << isNegative << " → " << (isNegative ? "Negativ" : "Positiv") << "\n";
    
    // Exponent
    cout << "\nSchritt 2 - Exponent:\n";
    int biasedExp = (fb.bits >> 23) & 0xFF;
    int unbiasedExp = biasedExp - 127;
    cout << "Bits 30-23: " << bitset<8>(biasedExp) << "\n";
    cout << "Biased Exponent: " << biasedExp << "\n";
    cout << "Unbiased Exponent (- 127): " << unbiasedExp << "\n";
    
    // Mantisse
    cout << "\nSchritt 3 - Mantisse:\n";
    uint32_t mantissa = fb.bits & 0x7FFFFF;
    cout << "Bits 22-0: " << bitset<23>(mantissa) << "\n";
    cout << "Normalisierte Form: 1.";
    for(int i = 22; i >= 0; i--) {
        cout << ((mantissa >> i) & 1);
    }
    cout << "\n";
    
    // Gesamtberechnung
    cout << "\nSchritt 4 - Berechnung:\n";
    float mantissaValue = 1.0f;
    for(int i = 22; i >= 0; i--) {
        if((mantissa >> i) & 1) {
            mantissaValue += pow(2, -(23-i));
        }
    }
    cout << "Wert = (-1)^" << isNegative << " × " 
         << mantissaValue << " × 2^" << unbiasedExp << "\n";
}

void showAdditionSteps(float a, float b) {
    FloatBits fa{a}, fb{b};
    
    cout << "\n=== Addition Schritte ===\n";
    cout << "a = " << a << " (" << formatIEEE(fa.bits) << ")\n";
    cout << "b = " << b << " (" << formatIEEE(fb.bits) << ")\n";

    // Exponenten extrahieren
    int exp_a = ((fa.bits >> 23) & 0xFF) - 127;
    int exp_b = ((fb.bits >> 23) & 0xFF) - 127;
    
    cout << "\n1. Exponenten:\n";
    cout << "a: " << exp_a << ", b: " << exp_b << "\n";
    
    cout << "\n2. Mantissen (mit impliziter 1):\n";
    uint32_t mant_a = (fa.bits & 0x7FFFFF) | 0x800000;
    uint32_t mant_b = (fb.bits & 0x7FFFFF) | 0x800000;
    cout << "a: 1." << bitset<23>(fa.bits & 0x7FFFFF) << "\n";
    cout << "b: 1." << bitset<23>(fb.bits & 0x7FFFFF) << "\n";
    
    cout << "\n3. Ergebnis:\n";
    FloatBits result{a + b};
    cout << a << " + " << b << " = " << (a + b) << "\n";
    cout << "IEEE: " << formatIEEE(result.bits) << "\n";
}

void showMultiplicationSteps(float a, float b) {
    FloatBits fa{a}, fb{b};
    
    cout << "\n=== Multiplikation Schritte ===\n";
    cout << "a = " << a << " (" << formatIEEE(fa.bits) << ")\n";
    cout << "b = " << b << " (" << formatIEEE(fb.bits) << ")\n";

    cout << "\n1. Vorzeichen:\n";
    bool sign_a = fa.bits >> 31;
    bool sign_b = fb.bits >> 31;
    bool final_sign = sign_a ^ sign_b;
    cout << "Ergebnis-Vorzeichen = " << sign_a << " XOR " << sign_b 
         << " = " << final_sign << "\n";
    
    cout << "\n2. Exponenten:\n";
    int exp_a = ((fa.bits >> 23) & 0xFF) - 127;
    int exp_b = ((fb.bits >> 23) & 0xFF) - 127;
    cout << exp_a << " + " << exp_b << " = " << (exp_a + exp_b) << "\n";
    
    FloatBits result{a * b};
    cout << "\n3. Ergebnis:\n";
    cout << a << " × " << b << " = " << (a * b) << "\n";
    cout << "IEEE: " << formatIEEE(result.bits) << "\n";
}

float getRandomFloat() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(-10.0f, 10.0f);
    return dis(gen);
}

int getRandomOperation() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 5);
    return dis(gen);
}

void generateTask(int operation) {
    FloatBits fb1, fb2, result;
    float num1, num2;
    
    switch(operation) {
        case 1: // Addition
            num1 = getRandomFloat();
            num2 = getRandomFloat();
            cout << "Addiere diese IEEE-754 Zahlen:\n";
            cout << formatIEEE(FloatBits{num1}.bits) << "\n";
            cout << formatIEEE(FloatBits{num2}.bits) << "\n";
            cout << "\nDruecke Enter für die Loesung...";
            cin.get();
            result.f = num1 + num2;
            cout << "\nLoesung: " << result.f << "\n";
            cout << "In IEEE-754: " << formatIEEE(result.bits) << "\n";
            
            cout << "\nMoechtest du den Rechenweg sehen? (j/n): ";
            char show_steps;
            cin >> show_steps;
            cin.ignore();
            if(show_steps == 'j' || show_steps == 'J') {
                showAdditionSteps(num1, num2);
            }
            break;

        case 2: // Subtraktion
            num1 = getRandomFloat();
            num2 = getRandomFloat();
            cout << "Subtrahiere diese IEEE-754 Zahlen:\n";
            cout << formatIEEE(FloatBits{num1}.bits) << "\n";
            cout << formatIEEE(FloatBits{num2}.bits) << "\n";
            cout << "\nDruecke Enter für die Loesung...";
            cin.get();
            result.f = num1 - num2;
            cout << "\nLoesung: " << result.f << "\n";
            cout << "In IEEE-754: " << formatIEEE(result.bits) << "\n";
            
            cout << "\nMoechtest du den Rechenweg sehen? (j/n): ";
            cin >> show_steps;
            cin.ignore();
            if(show_steps == 'j' || show_steps == 'J') {
                showAdditionSteps(num1, -num2);
            }
            break;

        case 3: // Multiplikation
            num1 = getRandomFloat();
            num2 = getRandomFloat();
            cout << "Multipliziere diese IEEE-754 Zahlen:\n";
            cout << formatIEEE(FloatBits{num1}.bits) << "\n";
            cout << formatIEEE(FloatBits{num2}.bits) << "\n";
            cout << "\nDruecke Enter für die Loesung...";
            cin.get();
            result.f = num1 * num2;
            cout << "\nLoesung: " << result.f << "\n";
            cout << "In IEEE-754: " << formatIEEE(result.bits) << "\n";
            
            cout << "\nMoechtest du den Rechenweg sehen? (j/n): ";
            cin >> show_steps;
            cin.ignore();
            if(show_steps == 'j' || show_steps == 'J') {
                showMultiplicationSteps(num1, num2);
            }
            break;

        case 4: // IEEE zu Dezimal
            num1 = getRandomFloat();
            cout << "Konvertiere diese IEEE-754 Zahl in Dezimal:\n";
            cout << formatIEEE(FloatBits{num1}.bits) << "\n";
            cout << "\nDruecke Enter für die Loesung...";
            cin.get();
            cout << "\nLoesung: " << num1 << "\n";
            
            cout << "\nMoechtest du den Rechenweg sehen? (j/n): ";
            cin >> show_steps;
            cin.ignore();
            if(show_steps == 'j' || show_steps == 'J') {
                showIEEESteps(num1);
            }
            break;

        case 5: // Dezimal zu IEEE
            num1 = getRandomFloat();
            cout << "Konvertiere diese Dezimalzahl in IEEE-754:\n";
            cout << fixed << setprecision(6) << num1 << "\n";
            cout << "\nDruecke Enter für die Loesung...";
            cin.get();
            cout << "\nLoesung: " << formatIEEE(FloatBits{num1}.bits) << "\n";
            
            cout << "\nMoechtest du den Rechenweg sehen? (j/n): ";
            cin >> show_steps;
            cin.ignore();
            if(show_steps == 'j' || show_steps == 'J') {
                showIEEESteps(num1);
            }
            break;
    }
}

bool isValidIEEE(const string& input) {
    if(input.length() != 32) return false;
    for(char c : input) {
        if(c != '0' && c != '1') return false;
    }
    return true;
}

uint32_t stringToIEEE(const string& input) {
    bitset<32> bits(input);
    return bits.to_ulong();
}

void calculateCustomInput() {
    string ieee1, ieee2;
    char operation;
    FloatBits num1, num2, result;

    cout << "Gib die erste 32-bit IEEE Zahl ein (ohne Leerzeichen): ";
    cin >> ieee1;
    while(!isValidIEEE(ieee1)) {
        cout << "Ungueltige Eingabe! Bitte gib eine 32-stellige Binaerzahl ein: ";
        cin >> ieee1;
    }
    num1.bits = stringToIEEE(ieee1);

    cout << "Waehle die Operation (+, -, *): ";
    cin >> operation;
    while(operation != '+' && operation != '-' && operation != '*') {
        cout << "Ungueltige Operation! Bitte wähle +, - oder *: ";
        cin >> operation;
    }

    cout << "Gib die zweite 32-bit IEEE Zahl ein (ohne Leerzeichen): ";
    cin >> ieee2;
    while(!isValidIEEE(ieee2)) {
        cout << "Ungueltige Eingabe! Bitte gib eine 32-stellige Binaerzahl ein: ";
        cin >> ieee2;
    }
    num2.bits = stringToIEEE(ieee2);

    cout << "\nEingabe 1: " << formatIEEE(num1.bits) << " = " << num1.f << "\n";
    cout << "Eingabe 2: " << formatIEEE(num2.bits) << " = " << num2.f << "\n";

    switch(operation) {
        case '+':
            result.f = num1.f + num2.f;
            cout << "\nAddition:\n";
            break;
        case '-':
            result.f = num1.f - num2.f;
            cout << "\nSubtraktion:\n";
            break;
        case '*':
            result.f = num1.f * num2.f;
            cout << "\nMultiplikation:\n";
            break;
    }

    cout << "Ergebnis: " << result.f << "\n";
    cout << "In IEEE-754: " << formatIEEE(result.bits) << "\n";

    cout << "\nMoechtest du den Rechenweg sehen? (j/n): ";
    char show_steps;
    cin >> show_steps;
    cin.ignore();
    
    if(show_steps == 'j' || show_steps == 'J') {
        switch(operation) {
            case '+':
                showAdditionSteps(num1.f, num2.f);
                break;
            case '-':
                showAdditionSteps(num1.f, -num2.f);
                break;
            case '*':
                showMultiplicationSteps(num1.f, num2.f);
                break;
        }
    }
}

int main() {
    char continue_program = 'j';
    
    while (continue_program == 'j' || continue_program == 'J') {
        cout << "\nWillkommen zum IEEE-754 Trainer!\n";
        cout << "1: Manuelle Auswahl des Aufgabentyps\n";
        cout << "2: Zufaellige Aufgabe\n";
        cout << "3: Eigene IEEE Zahlen eingeben\n";
        cout << "Waehle (1/2/3): ";
        
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 3) {
            calculateCustomInput();
        }
        else if (choice == 1) {
            cout << "\nWaehle eine Operation:\n";
            cout << "1: Addition\n";
            cout << "2: Subtraktion\n";
            cout << "3: Multiplikation\n";
            cout << "4: IEEE zu Dezimal\n";
            cout << "5: Dezimal zu IEEE\n";
            cout << "Waehle (1-5): ";
            int operation;
            cin >> operation;
            cin.ignore();
            generateTask(operation);
        }
        else if (choice == 2) {
            generateTask(getRandomOperation());
        }

        cout << "\nMoechtest du eine weitere Aufgabe? (j/n): ";
        cin >> continue_program;
        cin.ignore();
    }

    return 0;
}
