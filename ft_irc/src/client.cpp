#include "../inc/Client.hpp"

Client::Client(int fd) : clientfd(fd), log_in_status(false)
{
}

Client::~Client()
{
}

int Client::getClientfd() const
{
  return clientfd;
}

void Client::setUsername(const std::string &username)
{
  this->username = username;
}

std::string Client::getUsername() const
{
  return username;
}

void Client::setLoginStatus(bool status)
{
  log_in_status = status;
}

bool Client::getLoginStatus() const
{
  return log_in_status;
}

void Client::addGroup(Group *group)
{
  chatgroupList.push_back(group);
}

std::vector<Group *> Client::getGroups() const
{
  return chatgroupList;
}

Group::Group(const std::string &name) : groupName(name), inviteOnly(false), passwordOn(false), memberLimit(0), memberLimitOn(false), topic(""), topicBool(false), owner(NULL)
{
}

Group::~Group()
{
}

std::string Group::getGroupName() const
{
  return groupName;
}

void Group::setGroupName(const std::string &name)
{
  groupName = name;
}

void Group::addMember(Client *client)
{
  membersList.push_back(client);
}

void Group::removeMember(Client *client)
{
  membersList.erase(std::remove(membersList.begin(), membersList.end(), client), membersList.end());
}

void Group::addOperator(Client *client)
{
  operatorList.push_back(client);
}

void Group::removeOperator(Client *client)
{
  operatorList.erase(std::remove(operatorList.begin(), operatorList.end(), client), operatorList.end());
}

bool Group::isOperator(Client *client) const
{
  return std::find(operatorList.begin(), operatorList.end(), client) != operatorList.end();
}

void Group::setOwner(Client *client)
{
  owner = client;
}

Client* Group::getOwner() const
{
  return owner;
}

void Group::setInviteOnly(bool inviteOnly)
{
  this->inviteOnly = inviteOnly;
}

bool Group::getInviteOnly() const
{
  return inviteOnly;
}

void Group::setPassword(const std::string &password)
{
  this->password = password;
}

std::string Group::getPassword() const
{
  return password;
}

void Group::setPasswordOn(bool passwordOn)
{
  this->passwordOn = passwordOn;
}

bool Group::getPasswordOn() const
{
  return passwordOn;
}

void Group::setMemberLimit(int limit)
{
  memberLimit = limit;
}

int Group::getMemberLimit() const
{
  return memberLimit;
}

void Group::setMemberLimitOn(bool memberLimitOn)
{
  this->memberLimitOn = memberLimitOn;
}

bool Group::getMemberLimitOn() const
{
  return memberLimitOn;
}

void Group::setTopic(const std::string &topic)
{
  this->topic = topic;
}

std::string Group::getTopic() const
{
  return topic;
}

void Group::setTopicBool(bool topicBool)
{
  this->topicBool = topicBool;
}

bool Group::getTopicBool() const
{
  return topicBool;
}

void Group::addCurrentlySignedIn(Client *client)
{
  currentlySignedIn.push_back(client);
}

std::vector<Client *> Group::getCurrentlySignedIn() const
{
  return currentlySignedIn;
}

std::vector<Client *> Group::getMembersList() const
{
  return membersList;
}

std::vector<Client *> Group::getOperatorList() const
{
  return operatorList;
}