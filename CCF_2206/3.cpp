#include <iostream>
#include <cstdio>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Character {
public:
    set<string> actions;
    set<string> resTypes;
    set<string> resNames;

    Character(const set<string>& _actions, const set<string>& _resTypes,
        const set<string>& _resNames): actions(_actions),
        resTypes(_resTypes), resNames(_resNames) {}
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m, q, nv, no, nn, ns, ng;
    cin >> n >> m >> q;
    unordered_map<string, Character*> characterMap;
    string name, action, resType, resName;
    for (int i = 0; i < n; i++) {
        set<string> actions;
        set<string> resTypes;
        set<string> resNames;
        cin >> name >> nv;
        for (int j = 0; j < nv; j++) {
            cin >> action;
            actions.insert(action);
        }
        cin >> no;
        for (int j = 0; j < no; j++) {
            cin >> resType;
            resTypes.insert(resType);
        }
        cin >> nn;
        for (int j = 0; j < nn; j++) {
            cin >> resName;
            resNames.insert(resName);
        }
        characterMap[name] = new Character(actions, resTypes, resNames);
    }
    unordered_map<string, set<string>> groupMap;
    unordered_map<string, set<string>> userMap;
    string type, ugName;
    for (int i = 0; i < m; i++) {
        cin >> name >> ns;
        for (int j = 0; j < ns; j++) {
            cin >> type >> ugName;
            if (type == "u") {
                if (userMap.find(ugName) == userMap.end())
                    userMap[ugName] = {};
                userMap[ugName].insert(name);
            } else if (type == "g") {
                if (groupMap.find(ugName) == groupMap.end())
                    groupMap[ugName] = {};
                groupMap[ugName].insert(name);
            }
        }
    }
    for (int i = 0; i < q; i++) {
        string userName, groupName;
        vector<string> groupNames;
        cin >> userName >> ng;
        for (int j = 0; j < ng; j++) {
            cin >> groupName;
            groupNames.push_back(groupName);
        }
        cin >> action >> resType >> resName;

        set<Character*> characterSet;
        if (userMap.find(userName) != userMap.end()) {
            set<string> nameSet = userMap[userName];
            for (string s: nameSet) {
                if (characterMap.find(s) != characterMap.end())
                    characterSet.insert(characterMap[s]);
            }
        }
        for(string s: groupNames) {
            if (groupMap.find(s) != groupMap.end()) {
                set<string> nameSet = groupMap[s];
                for (string s: nameSet) {
                    if (characterMap.find(s) != characterMap.end())
                        characterSet.insert(characterMap[s]);
                }
            }
        }
        int res = 0;
        for(Character* c: characterSet) {
            const set<string>& cActions = c->actions;
            if (cActions.find("*") == cActions.end() && 
                cActions.find(action) == cActions.end()) continue;
            const set<string>& cResTypes = c->resTypes;
            if (cResTypes.find("*") == cResTypes.end() && 
                cResTypes.find(resType) == cResTypes.end()) continue;
            const set<string>& cResNames = c->resNames;
            if (cResNames.size() != 0 && 
                cResNames.find(resName) == cResNames.end()) continue;
            res = 1;
            break;
        }
        cout << res << endl;
    }
    return 0;
}