//
//  day20.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 1/3/24.
//

#include "day20.hpp"
#include "../helpers/file-helpers.hpp"

using namespace std;

long long gcd2(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm2(long long a, long long b) {
    return (a / gcd2(a, b)) * b;
}

long long lcm_of_array(const std::vector<long long>& numbers) {
    if (numbers.empty()) {
        return 0;  // or some appropriate default value
    }

    long long result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        result = lcm2(result, numbers[i]);
    }

    return result;
}

void pushButton(unordered_map<string, vector<string>>& pulseMap, queue<tuple<string, string, bool>>& pulseQueue, long long& lowPulseCount)
{
    for (auto& modId : pulseMap["b"])
    {
        pulseQueue.push( { "", modId, 0 } );
        lowPulseCount++;
    }
}

long long buttonPressesForRxPart2()
{
    vector<string> moduleConfiguration { convertFileToLines("./day-20/day20input.txt") };
    
    
    // Each module can be accessed by it's module id
    // The pair for a module id includes the module type (either '%', '&', or 'b')
    // And then another map for state
    // If '%' the state is simply "on" and 1 or 0 (true or false)
    // If '&' the state is a map of the incoming module connections and the last remember pulse type
    // (e.g. ("qp", 1), ("dx", 0) would indicate "qp" last sent a high pulse (1) and "dx" last sent a low pulse (0)
    // The broadcast module type (indicated by 'b') has no state
    unordered_map<string, pair<char, unordered_map<string, bool>>> modules { };
    
    unordered_map<string, vector<string>> pulseMap { };
    
    // The tuple is sender, reciever, pulse type (0 low, 1 high)
    queue<tuple<string, string, bool>> pulseQueue  { };
    
    long long lowPulseCount { 0 };
    long long highPulseCount { 0 };

    
    for (auto& mod : moduleConfiguration)
    {
        string modId;
        
        if (mod[0] == 'b')
        {
            modId = "b";
        }
        else
        {
            modId = mod.substr(1, 2);
        }
        
        size_t pos = mod.find("->");
        
        string moduleOutput;
        
        istringstream iss(mod.substr(pos + 2));
        
        while (getline(iss >> ws, moduleOutput, ','))
        {
            pulseMap[modId].push_back(moduleOutput);
        }
    }
    
    /*
    for (auto& pId : pulseMap)
    {
        std::cout << "Key: " << pId.first << '\n';
        
        std::cout << "Children: ";
        
        for (auto& val : pId.second)
        {
            std::cout << val << " ";
        }
        std::cout << '\n';
    }
     */
    
    for (auto& mod : moduleConfiguration)
    {
        if (mod[0] == '%')
        {
            modules[mod.substr(1, 2)].first = '%';
            modules[mod.substr(1, 2)].second["on"] = 0;

        }
        else if (mod[0] == '&')
        {
            modules[mod.substr(1, 2)].first = '&';
            
            for (auto& modChild : moduleConfiguration)
            {
                
                if (modChild[0] == 'b')
                {
                    continue;
                }
                
                string modToMatch { mod.substr(1, 2) };
                
                size_t pos = modChild.find("->");
                
                istringstream iss(modChild.substr(pos + 2));
                
                string moduleOutput;
                
                while (getline(iss >> ws, moduleOutput, ','))
                {
                    if (moduleOutput == modToMatch)
                    {
                        modules[modToMatch].second[modChild.substr(1, 2)] = 0;
                    }
                }
            }
        }
        else
        {
            modules["b"].first = 'b';
        }
    }
    
    /*
    for (const auto& module : modules) {
           std::cout << "Module: " << module.first << std::endl;
           std::cout << " - Module Type: " << module.second.first << std::endl;
           std::cout << " - State:" << std::endl;

           for (const auto& submodule : module.second.second) {
               std::cout << "   - " << submodule.first << ": " << (submodule.second ? "true" : "false") << std::endl;
           }

           std::cout << std::endl;
    }
     */
    
    
    long long buttonPressCount { 0 };
    
    bool chFirstTrue { true };
    bool ghFirstTrue { true };
    bool svFirstTrue { true };
    bool thFirstTrue { true };
    
    long long buttonPressCountCh { 0 };
    long long buttonPressCountGh { 0 };
    long long buttonPressCountSv { 0 };
    long long buttonPressCountTh { 0 };



    
    
    while (chFirstTrue || ghFirstTrue || svFirstTrue || thFirstTrue)
    {
        lowPulseCount++;
        pushButton(pulseMap, pulseQueue, lowPulseCount);
        buttonPressCount++;
            
        // While the pulseQueue containts elements, process them
        
        while (!pulseQueue.empty())
        {
            tuple<string, string, bool> pulse { pulseQueue.front() };
            pulseQueue.pop();
            
            char modType { modules[get<1>(pulse)].first };
            
            if (modType == '%')
            {
                // If the pulse is a high pulse do nothing
                if (get<2>(pulse) == 1)
                {
                    continue;
                }
                else
                {
                    bool on = modules[get<1>(pulse)].second["on"];
                    
                    if (on)
                    {
                        modules[get<1>(pulse)].second["on"] = 0;
                        for (auto& output : pulseMap[get<1>(pulse)])
                        {
                            lowPulseCount++;
                            pulseQueue.push({ get<1>(pulse), output, 0 });
                        }
                    }
                    else
                    {
                        modules[get<1>(pulse)].second["on"] = 1;
                        for (auto& output : pulseMap[get<1>(pulse)])
                        {
                            highPulseCount++;
                            pulseQueue.push({ get<1>(pulse), output, 1 });
                        }
                    }
                }
                
            }
            else if (modType == '&')
            {
               
                
                modules[get<1>(pulse)].second[get<0>(pulse)] = get<2>(pulse);
                
                if (get<1>(pulse) == "cn")
                {
                    for (const auto& submodule : modules[get<1>(pulse)].second) {
                        
                        if (submodule.first == "ch" && submodule.second == true && chFirstTrue)
                        {
                            chFirstTrue = false;
                            buttonPressCountCh = buttonPressCount;
                            
                        }
                        else if (submodule.first == "gh" && submodule.second == true && ghFirstTrue)
                        {
                            ghFirstTrue = false;
                            buttonPressCountGh = buttonPressCount;
                        }
                        else if (submodule.first == "sv" && submodule.second == true && svFirstTrue)
                        {
                            svFirstTrue = false;
                            buttonPressCountSv = buttonPressCount;
                        }
                        else if (submodule.first == "th" && submodule.second == true && thFirstTrue)
                        {
                            thFirstTrue = false;
                            buttonPressCountTh = buttonPressCount;
                        }
                    }
                    
                }
                
                bool allHigh { true };
                
                for (auto& input : modules[get<1>(pulse)].second)
                {
                    if (input.second == 0)
                    {
                        allHigh = false;
                        break;
                    }
                }
                
                if (allHigh)
                {
                    
                    for (auto& output : pulseMap[get<1>(pulse)])
                    {
                    
                        lowPulseCount++;
                        pulseQueue.push({ get<1>(pulse), output, 0 });
                    }
                    
                }
                else
                {
                    
                    for (auto& output : pulseMap[get<1>(pulse)])
                    {
                        highPulseCount++;
                        pulseQueue.push({ get<1>(pulse), output, 1 });
                    }
                    
                }
            }
        }
        
    }
    
    std::cout << "ch count: " << buttonPressCountCh << '\n';
    std::cout << "gh count: " << buttonPressCountGh << '\n';
    std::cout << "sv count: " << buttonPressCountSv << '\n';
    std::cout << "th count: " << buttonPressCountTh << '\n';
    
    vector<long long> buttonPressCountVector { buttonPressCountCh, buttonPressCountGh,
        buttonPressCountSv, buttonPressCountTh
    };
    
    return lcm_of_array(buttonPressCountVector);
}

long long lowPulseTimesHighPart1()
{
    vector<string> moduleConfiguration { convertFileToLines("./day-20/day20input.txt") };
    
    
    // Each module can be accessed by it's module id
    // The pair for a module id includes the module type (either '%', '&', or 'b')
    // And then another map for state
    // If '%' the state is simply "on" and 1 or 0 (true or false)
    // If '&' the state is a map of the incoming module connections and the last remember pulse type
    // (e.g. ("qp", 1), ("dx", 0) would indicate "qp" last sent a high pulse (1) and "dx" last sent a low pulse (0)
    // The broadcast module type (indicated by 'b') has no state
    unordered_map<string, pair<char, unordered_map<string, bool>>> modules { };
    
    unordered_map<string, vector<string>> pulseMap { };
    
    // The tuple is sender, reciever, pulse type (0 low, 1 high)
    queue<tuple<string, string, bool>> pulseQueue  { };
    
    long long lowPulseCount { 0 };
    long long highPulseCount { 0 };

    
    for (auto& mod : moduleConfiguration)
    {
        string modId;
        
        if (mod[0] == 'b')
        {
            modId = "b";
        }
        else
        {
            modId = mod.substr(1, 2);
        }
        
        size_t pos = mod.find("->");
        
        string moduleOutput;
        
        istringstream iss(mod.substr(pos + 2));
        
        while (getline(iss >> ws, moduleOutput, ','))
        {
            pulseMap[modId].push_back(moduleOutput);
        }
    }
    
    /*
    for (auto& pId : pulseMap)
    {
        std::cout << "Key: " << pId.first << '\n';
        
        std::cout << "Children: ";
        
        for (auto& val : pId.second)
        {
            std::cout << val << " ";
        }
        std::cout << '\n';
    }
     */
    
    for (auto& mod : moduleConfiguration)
    {
        if (mod[0] == '%')
        {
            modules[mod.substr(1, 2)].first = '%';
            modules[mod.substr(1, 2)].second["on"] = 0;

        }
        else if (mod[0] == '&')
        {
            modules[mod.substr(1, 2)].first = '&';
            
            for (auto& modChild : moduleConfiguration)
            {
                
                if (modChild[0] == 'b')
                {
                    continue;
                }
                
                string modToMatch { mod.substr(1, 2) };
                
                size_t pos = modChild.find("->");
                
                istringstream iss(modChild.substr(pos + 2));
                
                string moduleOutput;
                
                while (getline(iss >> ws, moduleOutput, ','))
                {                    
                    if (moduleOutput == modToMatch)
                    {
                        modules[modToMatch].second[modChild.substr(1, 2)] = 0;
                    }
                }
            }
        }
        else
        {
            modules["b"].first = 'b';
        }
    }
    
    /*
    for (const auto& module : modules) {
           std::cout << "Module: " << module.first << std::endl;
           std::cout << " - Module Type: " << module.second.first << std::endl;
           std::cout << " - State:" << std::endl;

           for (const auto& submodule : module.second.second) {
               std::cout << "   - " << submodule.first << ": " << (submodule.second ? "true" : "false") << std::endl;
           }

           std::cout << std::endl;
    }
    */
    
    
    for (int i { 0 }; i < 1000; ++i)
    {
        lowPulseCount++;
        pushButton(pulseMap, pulseQueue, lowPulseCount);
            
        // While the pulseQueue containts elements, process them
        
        while (!pulseQueue.empty())
        {
            tuple<string, string, bool> pulse { pulseQueue.front() };
            pulseQueue.pop();
            
            char modType { modules[get<1>(pulse)].first };
            
            if (modType == '%')
            {
                // If the pulse is a high pulse do nothing
                if (get<2>(pulse) == 1)
                {
                    continue;
                }
                else
                {
                    bool on = modules[get<1>(pulse)].second["on"];
                    
                    if (on)
                    {
                        modules[get<1>(pulse)].second["on"] = 0;
                        for (auto& output : pulseMap[get<1>(pulse)])
                        {
                            lowPulseCount++;
                            pulseQueue.push({ get<1>(pulse), output, 0 });
                        }
                    }
                    else
                    {
                        modules[get<1>(pulse)].second["on"] = 1;
                        for (auto& output : pulseMap[get<1>(pulse)])
                        {
                            highPulseCount++;
                            pulseQueue.push({ get<1>(pulse), output, 1 });
                        }
                    }
                }
                
            }
            else if (modType == '&')
            {
                modules[get<1>(pulse)].second[get<0>(pulse)] = get<2>(pulse);
                
                bool allHigh { true };
                
                for (auto& input : modules[get<1>(pulse)].second)
                {
                    if (input.second == 0)
                    {
                        allHigh = false;
                        break;
                    }
                }
                
                if (allHigh)
                {
                    
                    for (auto& output : pulseMap[get<1>(pulse)])
                    {
                        lowPulseCount++;
                        pulseQueue.push({ get<1>(pulse), output, 0 });
                    }
                    
                }
                else
                {
                    
                    for (auto& output : pulseMap[get<1>(pulse)])
                    {
                        highPulseCount++;
                        pulseQueue.push({ get<1>(pulse), output, 1 });
                    }
                    
                }
            }
        }
        
    }
    
    
    std::cout << lowPulseCount << " " << highPulseCount << '\n';
    return lowPulseCount * highPulseCount;
}
