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
    void addMember(Client *client);
    void removeMember(Client *client);
    void addOperator(Client *client);
    void removeOperator(Client *client);
    bool isOperator(Client *client) const;
    void setInviteOnly(bool inviteOnly);
    bool getInviteOnly() const;
    void setPassword(const std::string &password);
    std::string getPassword() const;
    void setMemberLimit(int limit);
    int getMemberLimit() const;
    void setTopic(const std::string &topic);
    std::string getTopic() const;

  private:
    std::string groupName;
    std::vector<Client *> membersList;
    std::vector<Client *> operatorList;
    bool inviteOnly;
    std::string password;
    int memberLimit;
    std::string topic;
};

#endif
