#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <vector>
# include <algorithm>

class Group; // Forward declaration

class Client
{
  public:
    Client(int fd);
    ~Client();
    int getClientfd() const;
    void setUsername(const std::string &username);
    std::string getUsername() const;
    void setLoginStatus(bool status);
    bool getLoginStatus() const;
    void addGroup(Group *group);
    std::vector<Group *> getGroups() const;

  private:
    int clientfd;
    std::string username;
    bool log_in_status;
    std::vector<Group *> chatgroupList;
};

class Group
{
  public:
    Group(const std::string &name);
    ~Group();
    std::string getGroupName() const;
    void setGroupName(const std::string &name);
    void addMember(Client *client);
    void removeMember(Client *client);
    void addOperator(Client *client);
    void removeOperator(Client *client);
    bool isOperator(Client *client) const;
    void setOwner(Client *client);
    Client* getOwner() const;
    void setInviteOnly(bool inviteOnly);
    bool getInviteOnly() const;
    void setPassword(const std::string &password);
    std::string getPassword() const;
    void setPasswordOn(bool passwordOn);
    bool getPasswordOn() const;
    void setMemberLimit(int limit);
    int getMemberLimit() const;
    void setMemberLimitOn(bool memberLimitOn);
    bool getMemberLimitOn() const;
    void setTopic(const std::string &topic);
    std::string getTopic() const;
    void setTopicBool(bool topicBool);
    bool getTopicBool() const;
    void addCurrentlySignedIn(Client *client);
    std::vector<Client *> getCurrentlySignedIn() const;
    std::vector<Client *> getMembersList() const;
    std::vector<Client *> getOperatorList() const;

  private:
    std::string groupName;
    std::vector<Client *> membersList;
    std::vector<Client *> operatorList;
    std::vector<Client *> currentlySignedIn;
    bool inviteOnly;
    std::string password;
    bool passwordOn;
    int memberLimit;
    bool memberLimitOn;
    std::string topic;
    bool topicBool;
    Client* owner;
};

#endif