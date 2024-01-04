//
//  day19.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/29/23.
//

#include "day19.hpp"
#include "../helpers/file-helpers.hpp"

void dfsWorkflows(std::string node, std::vector<std::string>& currBounds, std::vector<std::vector<std::string>>& acceptedBounds, std::unordered_map<std::string, std::vector<std::string>>& workflowMap)
{
    
    if (node == "A")
    {
        acceptedBounds.push_back(currBounds);
        return;
    }
    
    if (node == "R")
    {
        return;
    }
    
    std::vector<std::string> children = workflowMap[node];
                    
    for (auto& child : children)
    {
        size_t pos = child.find_last_of(":");
        
        std::string test = child.substr(0, pos);
        std::string node = child.substr(pos + 1);
            
        currBounds.push_back(test);
        dfsWorkflows(node, currBounds, acceptedBounds, workflowMap);
        currBounds.pop_back();
        
    }
}

long long numberOfCombinationsPart2()
{
    std::vector<std::string> workflows { convertFileToLines("./day-19/day19input-workflows.txt") };

    std::unordered_map<std::string, std::vector<std::string>> workflowMap { };
    
    for (auto& wf : workflows)
    {
        // Remove the trailing '}'
        wf.pop_back();

        std::istringstream iss(wf);
        std::string workflowId;
      
        std::getline(iss, workflowId, '{');
        
        std::string currRules;
        std::string prevRules;
        
        while (std::getline(iss, currRules, ','))
        {
            
            std::string tempRule;
            std::string reversedPrevRules { "" };

            
            size_t lastColPos = prevRules.find_last_of(':');
            
            
            if (lastColPos != std::string::npos)
            {
                std::string unalteredPrevRules = prevRules.substr(0, lastColPos);

                tempRule = prevRules.substr(lastColPos + 1);
                
                std::string ratingToTest = tempRule.substr(0, 1);
                std::string opToUse = tempRule.substr(1, 1);
                std::string valueForComparison = tempRule.substr(2);
                                
                if (opToUse == ">")
                {
                    reversedPrevRules += (ratingToTest + "<=" + valueForComparison + ":");
                }
                else
                {
                    reversedPrevRules += (ratingToTest + ">=" + valueForComparison + ":");
                }
                
                if (unalteredPrevRules != "")
                {
                    reversedPrevRules = unalteredPrevRules + ":" + reversedPrevRules;
                }
                
            }
                        
            workflowMap[workflowId].push_back(reversedPrevRules + currRules);
            
            size_t lastColonPos = currRules.find_last_of(':');
            
            
            if (lastColonPos != std::string::npos)
            {
                currRules.erase(lastColonPos);
            }
            
            if (reversedPrevRules == "")
            {
                currRules = ":" + currRules;
            }

            
            prevRules = reversedPrevRules + currRules;
        }
    }
    
    std::vector<std::string> currBounds { };
    std::vector<std::vector<std::string>> acceptedBounds { };
    
    dfsWorkflows("in", currBounds, acceptedBounds, workflowMap);

    long long validCombos { 0 };
    
    for (auto& bounds : acceptedBounds)
    {
        
        std::unordered_map<std::string, std::vector<long long>> ranges {
            { "x", {1, 4000}},
            { "m", {1, 4000}},
            { "a", {1, 4000}},
            { "s", {1, 4000}}
        };
        
        for (auto& bound : bounds)
        {

            std::istringstream iss(bound);
            
            std::string inequality;
            
            while (getline(iss, inequality, ':'))
            {
                std::string workflowId { inequality[0] };
                long long num { 0 };

                if (inequality[2] == '=')
                {
                    num = stoll(inequality.substr(3));
                }
                else
                {
                    if (inequality[1] == '>')
                    {
                        num = (stoll(inequality.substr(2)) + 1);
                    }
                    else
                    {
                        num = (stoll(inequality.substr(2)) - 1);
                    }
                }
                
                if (inequality[1] == '>')
                {
                    ranges[workflowId][0] = std::max(ranges[workflowId][0], num);
                }
                else
                {
                    ranges[workflowId][1] = std::min(ranges[workflowId][1], num);
                }
            }
        }
        long long uniqueComboCount { 1 };
        
        for (auto& r : ranges)
        {
            uniqueComboCount *= ((r.second[1] - r.second[0]) + 1);
            
        }
        
        validCombos += uniqueComboCount;
    }


    
    return validCombos;
    
}




long long sumOfAcceptedPartRatings()
{
    std::vector<std::string> workflows { convertFileToLines("./day-19/day19input-workflows.txt") };
    std::vector<std::string> partNumbers { convertFileToLines("./day-19/day19input-partnumbers.txt") };


    std::unordered_map<std::string, std::vector<std::string>> workflowMap { };
    std::vector<std::unordered_map<std::string, long long>> partsMaps { };
    
    for (auto& part : partNumbers)
    {
        std::unordered_map<std::string, long long> partMap { };
        
        // Remove trailing '}'
        part.pop_back();
        // Remove the leading '{'
        part.erase(0, 1);
        
        std::istringstream iss(part);
        
        std::string partKeyPair;
        
        while (std::getline(iss, partKeyPair, ','))
        {
            size_t pos = partKeyPair.find('=');
            std::string key { partKeyPair.substr(0, pos) };
            long long val { stoll(partKeyPair.substr(pos + 1)) };
            
            partMap[key] = val;
        }
        
        partsMaps.push_back(partMap);
    }
    
    for (auto& wf : workflows)
    {
        // Remove the trailing '}'
        wf.pop_back();

        std::istringstream iss(wf);
        std::string workflowId;
        
        std::getline(iss, workflowId, '{');
        
        std::string rule;
        
        while (std::getline(iss, rule, ','))
        {
            workflowMap[workflowId].push_back(rule);
        }
    }
    
    // Process all the parts
    
    long long acceptedPartSum { 0 };
    
    for (auto& partMap : partsMaps)
    {
        std::string finalStatus = processPart(partMap, workflowMap);
        
        if (finalStatus == "A")
        {
            for (const auto& p : partMap)
            {
                acceptedPartSum += p.second;
            }
        }
    }
    
    return acceptedPartSum;
}

std::string processPart(std::unordered_map<std::string, long long>& partMap, std::unordered_map<std::string, std::vector<std::string>>& workflowMap)
{
    std::string nextWorkflow = "in";
    
    std::vector<std::string> ruleList;
    
    while (nextWorkflow != "A" && nextWorkflow != "R")
    {
        ruleList = workflowMap[nextWorkflow];
                
        for (auto& rule : ruleList)
        {
            size_t pos = rule.find(":");
            
            if (pos == std::string::npos)
            {
                nextWorkflow = rule;
                break;
            }
            else
            {
                std::string test = rule.substr(0, pos);
                std::string potentialNextWorkflow = rule.substr(pos + 1);
                
                std::string ratingToTest = test.substr(0, 1);
                std::string opToUse = test.substr(1, 1);
                std::string valueForComparison = test.substr(2);
                
                long long partValue = partMap[ratingToTest];
                
                if (opToUse == ">")
                {
                    if (partValue > stoll(valueForComparison))
                    {
                        nextWorkflow = potentialNextWorkflow;
                        break;
                    }
                }
                else
                {
                    if (partValue < stoll(valueForComparison))
                    {
                        nextWorkflow = potentialNextWorkflow;
                        break;
                    }
                }
            }
        }
    }
    
    return nextWorkflow;
}
