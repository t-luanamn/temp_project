#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <vector>
# include <algorithm>

class Group; // Forward declaration

class Client
{
  public:
    Client(int clientfd);
    ~Client();

    bool isRegistered() const;
    void setRegistered(bool registered);

    int getClientfd() const;
    std::string getUsername() const;
    void setUsername(const std::string &username);
    bool isLoggedIn() const;
    void setLoggedIn(bool status);
    std::vector<Group *> getGroups() const;

    // Methods to manage client connection state
    void setPassReceived(bool received);
    void setNickReceived(bool received);
    void setUserReceived(bool received);

  private:
    int _clientfd;
    bool _registered;
    std::string username;
    bool log_in_status;
    std::vector<Group *> chatgroupList;

    // Member variables to track connection state
    bool passReceived;
    bool nickReceived;
    bool userReceived;
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