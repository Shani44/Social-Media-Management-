#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class SocialMedia;
class UserProfile
{
public:
    string name;
    static int id;
    vector<string> interests;
    string city;
    string institution;
    vector<string> hobbies;
    vector<SocialMedia> chats;
    UserProfile() {}

    UserProfile(string n, vector<string> inter, string c, string inst, vector<string> h)
    {
        name = n;
        id++;
        interests = inter;
        hobbies = h;
        city = c;
        institution = inst;
    }

    void displayProfile()
    {
        cout << "Name:" << name << endl;
        cout << "ID:" << id << endl;
        cout << "Interests:";
        for (int i = 0; i < interests.size(); i++)
        {
            cout << interests[i] << " ";
        }
        cout << endl;
        cout << "City:" << city << endl;
        cout << "Institution:" << institution << endl;
        cout << "Hobbies:";
        for (int i = 0; i < hobbies.size(); i++)
        {
            cout << hobbies[i] << " ";
        }
        cout << endl;
    }
};

int UserProfile::id = 0;


class UserConnects {
public:
    UserProfile userProfile;
    vector<UserConnects> friends;


    UserConnects() {}

    UserConnects(UserProfile _user) {
        userProfile = _user;
    }


    void addFriend(UserConnects userConnect) {
        friends.push_back(userConnect);
    }

    UserConnects deleteFriend(string name) {
        UserConnects user;
        for (int i = 0; i < friends.size(); i++) {
            if (name == friends[i].userProfile.name) {
                user = friends[i];
                friends.erase(friends.begin() + i);
            }
        }
        return user;
    }

    void displayAllFriends() {
        for (int i = 0; i < friends.size(); i++) {
            cout << (friends[i].userProfile.name) << endl;
        }
    }

    void seeMutualFriends(UserConnects userConnect) {

        vector<string> mutualFriends;
        for (int i = 0; i < friends.size(); i++) {
            for (int j = 0; j < userConnect.friends.size(); j++) {
                if (friends[i].userProfile.name == userConnect.friends[j].userProfile.name) {
                    mutualFriends.push_back(friends[i].userProfile.name);
                }
            }
        }

        cout << "Mutual Friends :" << endl;
        for (int i = 0; i < mutualFriends.size(); i++) {
            cout << mutualFriends[i] << endl;
        }
    }

    void suggestUsers(vector<UserConnects> users,UserConnects user,  string searchBase) {
        vector<string> names;
        if (searchBase == "institution") {
            for (int i = 0; i < users.size(); i++) {
                if (userProfile.institution == users[i].userProfile.institution && userProfile.name != users[i].userProfile.name) {
                    names.push_back(users[i].userProfile.name);
                }
            }
        }
        else if (searchBase == "city") {
            for (int i = 0; i < users.size(); i++) {
                if (userProfile.city == users[i].userProfile.city && userProfile.name != users[i].userProfile.name) {
                    names.push_back(users[i].userProfile.name);
                }
            }
        }
        else if (searchBase == "interests") {
            for (int i = 0; i < users.size(); i++) {
                for (int j = 0; j < user.userProfile.interests.size(); j++) {
                    if (user.userProfile.interests[j] == users[i].userProfile.interests[j] && user.userProfile.name != users[i].userProfile.name) {
                        names.push_back(users[i].userProfile.name);
                    }
                }
            }
        }
        cout << "Suggested friends :" << endl;
        for (int i = 0; i < names.size(); i++) {
            cout << names[i] << endl;
        }

    }

};

class Message {
public:
    static int id;
    UserProfile* sender;
    string message;
    UserProfile* receiver;
    Message(UserProfile* _sender, string _message, UserProfile* _receiver) {
        sender = _sender;
        id++;
        receiver = _receiver;
        message = _message;
    }
    void displayMessage()
    {
        cout << "Sender:" << sender->name << endl;
        cout << "Message:" << message << endl;
        cout << "Receiver:" << receiver->name << endl;
    }
};

int Message::id = 0;

class PostData {
public:
    string content;
    UserConnects* owner;
};

class CommentData {
public:
    string content;
    UserConnects* owner;
};

class Post {
public:
    static int id;
    PostData post;
    vector<CommentData> comments;
    Post(){}
    Post(PostData _post) {
        id++;
        post = _post;
    }



};

int Post::id = 0;

Post searchPost(string post, vector<Post> posts) {
    Post postReturn;
    for (int i = 0; i < posts.size(); i++) {
        if (posts[i].post.content == post) {
            postReturn = posts[i];
            break;
        }
    }
    return postReturn;
    cout << "User not found" << endl;
}

Post deletePost(string content, vector<Post>& posts) {
    Post post;
    for (int i = 0; i < posts.size(); i++) {
        if (posts[i].post.content == content) {
            post = posts[i];
            posts.erase(posts.begin() + i);
            break;
        }
    }
    return post;
}

void addComment(Post post, CommentData comment, vector<Post>& posts) {
    for (int i = 0; i < posts.size(); i++) {
        if (post.post.content == posts[i].post.content) {
            posts[i].comments.push_back(comment);
        }
    }
}



void displayAllComments(string content, vector<Post> posts) {
    Post post = searchPost(content, posts);
    for (int i = 0; i < post.comments.size(); i++) {
        cout << post.comments[i].content << endl;
    }
}
void displayAllPost(vector<Post> posts) {
    for (int i = 0; i < posts.size(); i++) {
        cout << posts[i].post.content << endl;
   }
}

class Group {
public:
    string name;
    vector<UserConnects> users;
    Group(){}
    Group(string _name, vector<UserConnects> _users) {
        name = _name;
        users = _users;
    }
    void getAllUsersFromGroup() {
        for (int i = 0; i < users.size(); i++) {
            cout << users[i].userProfile.name << endl;
        }
    }

    void joinGroup(UserConnects newUser) {
        users.push_back(newUser);
    }
};

class SocialMedia {
public:
    stack<Message> messages;
    void sendMessage(UserProfile* sender, string message, UserProfile* receiver)
    {
        Message newMessage(sender, message, receiver);
        messages.push(newMessage);

        //cout << "Message sent from " << sender->name << " to " << receiver->name << endl;
        
    }
    // usman ubaid
    void receiveMessages(UserProfile* user1, UserProfile* user2)
    {
        
        if (messages.top().receiver->name == user1->name) {
            
            cout << messages.top().message << endl;

        }
        else {
            cout << "\t\t\t\t" << messages.top().message << endl;
        }
            
    }
};

class Undo {
public:
    stack<Post> deletedPosts;
    stack<UserConnects> removedFriends;
    Undo(){}
    void addDeletedPost(Post post) {
        deletedPosts.push(post);
    }

    void addRemovedFriend(UserConnects user) {
        removedFriends.push(user);
    }

    UserConnects undoFriendRequest() {
        UserConnects user = removedFriends.top();
        removedFriends.pop();
        return user;
    }

    Post undoPost() {
        Post post = deletedPosts.top();
        deletedPosts.pop();
        return post;
    }
};


void insertNewUsers(UserConnects user, vector<UserConnects> users) {
    users.push_back(user);
}

void getAllUsers(vector<UserConnects> users) {
    for (int i = 0; i < users.size(); i++) {
        cout << users[i].userProfile.name << endl;
    }
}

UserConnects searchUser(string name, vector<UserConnects> users) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].userProfile.name == name) {
            return users[i];
        }
    }
    cout << "User not found" << endl;
}



void Messaging(UserProfile user1, UserProfile user2) {
    SocialMedia app;
    string message;
    cout << "Enter your message :";
    getline(cin, message);
    cin >> message;

    app.sendMessage(&user1, message, &user2);
    //app.sendMessage(&user2, "Wa alaikum-assalam!", &user1);

    user1.chats.push_back(app);
    user2.chats.push_back(app);


    cout << "Received Messages of " << user1.name << endl;
    app.receiveMessages(&user1, &user2);

    cout << "Send Messages to " << user2.name << endl;
    app.receiveMessages(&user2, &user1);
    system("PAUSE");
}


int main() {
    SocialMedia app;
    Undo undo;
    string message;
    vector<Post> posts;
    vector<UserConnects> users;
    vector<Group> groups;
    vector<UserConnects> usersInGroup;
    PostData postData;
    Post post;
    UserProfile sender;
    UserProfile receiver;
    Post searchedPost;
    CommentData comment;
    Group group;
    vector<string> interests, hobbies;
    string name;
    string city;
    string content;
    int size;
    string commentContent;
    string institution;
    UserProfile user;
    UserConnects connect;
    UserConnects user2;
    int n, choice;
start:
    system("cls");
    cout << "\n\n\n";
    cout << "\t\t\t\t  ------------" << "\n";
    cout << "\t\t\t\t      MENU" << "\n";
    cout << "\t\t\t\t  ------------" << "\n";
    cout << "\t\t\t     1. Make a new Account" << "\n";
    cout << "\t\t\t     2. Display All Users" << "\n";
    cout << "\t\t\t     3. Follow Others" << "\n";
    cout << "\t\t\t     4. Display All Friends " << "\n";
    cout << "\t\t\t     5. Display Mutual Friends " << "\n";
    cout << "\t\t\t     6. Suggest Users " << "\n";
    cout << "\t\t\t     7. Chat with Friends " << "\n";
    cout << "\t\t\t     8. Switch to another account " << "\n";
    cout << "\t\t\t     9. Make a group " << "\n";
    cout << "\t\t\t     10. Create a Post " << "\n";
    cout << "\t\t\t     11. News Feed " << "\n";
    cout << "\t\t\t     12. Add A Comment " << "\n";
    cout << "\t\t\t     13. Display Profile " << "\n";
    cout << "\t\t\t     14. Display Group Users " << "\n";
    cout << "\t\t\t     15. Delete Post " << "\n";
    cout << "\t\t\t     16. Undo Deleted Post " << "\n";
    cout << "\t\t\t     17. Remove Friend " << "\n";
    cout << "\t\t\t     18. Undo Removed Friend " << "\n";
    cout << "\t\t\t     19. Exit" << "\n\n";
    cout << "\t\t\t     ENTER YOUR OPTION: ";
    cin >> n;
    system("cls");
    switch (n) {
    case 1:
        cout << "Enter your name :";
        cin >> name;
        cout << "Enter your city :";
        cin >> city;
        cout << "Enter your institution :";
        cin >> institution;

        cout << "Enter max 5 things you are interested :" << endl;
        cout << "How many items you want to add :";
        cin >> size;
        for (int i = 0; i < size; i++) {
            cin >> content;
            interests.push_back(content);
        }
        system("cls");
        cout << "Enter any 5 hobbies of yours :" << endl;
        cout << "How many items you want to add :";
        cin >> size;
        for (int i = 0; i < size; i++) {
            cin >> content;
            hobbies.push_back(content);
        }
        system("cls");
        user = UserProfile(name, interests, city, institution, hobbies);
        connect = UserConnects(user);
        users.push_back(connect);
        interests = {};
        break;
    case 2:
        getAllUsers(users);
        system("PAUSE");
        break;
    case 3:
        if (user.name == "") {
            cout << "You must have account to proceed" << endl;
            goto start;
        }
        getAllUsers(users);
        system("PAUSE");
        cout << "Enter name of the person to send request :";
        cin >> name;
        user2 = searchUser(name, users);
        /*if (user2.userProfile.name == user.name) {
            cout << "You could not follow yourself" << endl;
            system("PAUSE");
        }*/
        connect.addFriend(user2);
        system("PAUSE");
        connect.displayAllFriends();
        system("PAUSE");
        break;
    case 4:
        cout << "All Friends :-" << endl;
        connect.displayAllFriends();
        system("PAUSE");
        break;
    case 5:
        cout << "All Users :-" << endl;
        getAllUsers(users);
        system("PAUSE");
        cout << "Enter name of the person to see mutual friends :";
        cin >> name;
        user2 = searchUser(name, users);
        connect.seeMutualFriends(user2);
        system("PAUSE");
        break;
    case 6:
        cout << "Enter a number to select base on which mutual friends to be searched :";
        system("cls");
        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t  ------------" << "\n";
        cout << "\t\t\t\t      MENU" << "\n";
        cout << "\t\t\t\t  ------------" << "\n";
        cout << "\t\t\t     1. CITY" << "\n";
        cout << "\t\t\t     2. INSTITUTION" << "\n";
        cout << "\t\t\t     3. INTERESTS" << "\n";
        cout << "\t\t\t     ENTER YOUR OPTION: ";
        cin >> choice;
        system("cls");
        if (choice == 1) {
            connect.suggestUsers(users, user,"city");
        }
        else if (choice == 2) {
            connect.suggestUsers(users, user,"institution");
        }
        else if (choice == 3) {
            connect.suggestUsers(users, user,"interests");
        }
        else {
            cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tWRONG OPTION!";
            cout << "\n\n\n\n\n\n\n\n";
            system("PAUSE");
        }
        system("PAUSE");
        break;
    case 7:
        cout << "All Users :-" << endl;
        getAllUsers(users);
        system("PAUSE");
        cout << "Enter name of the person you want to chat with :";
        cin >> name;
        user2 = searchUser(name, users);
        sender = user2.userProfile;
        receiver = user;
        while (message != "end") {
            if (sender.name == user.name) {
                sender = user2.userProfile;
            }
            else if (sender.name == user2.userProfile.name) {
                sender = user;
            }

            if (receiver.name == user.name) {
                receiver = user2.userProfile;
            }
            else if (receiver.name == user2.userProfile.name) {
                receiver = user;
            }
            cout << "Enter " << sender.name <<   " message :";
            getline(cin, message);
            cin >> message;
            
            if (message == "end") break;
            app.sendMessage(&sender, message, &receiver); // messages queue

            app.receiveMessages(&user, &user2.userProfile);
        }
        
        
        user.chats.push_back(app);
        user2.userProfile.chats.push_back(app);
        
        app.receiveMessages(&user, &user2.userProfile);

        
        system("PAUSE");
        
        break;
    case 8:
        getAllUsers(users);
        system("PAUSE");
        cout << "Enter name of the person you want to login from :";
        cin >> name;
        user2 = searchUser(name, users);
        user = user2.userProfile;
        connect = user2;
        break;
    case 9:
        getAllUsers(users);
        cout << "Enter number of users in the group :";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << "User " << i + 1 << ": ";
            cin >> name;
            user2 = searchUser(name, users);
            group.joinGroup(user2);
        }
        system("PAUSE");
        group.getAllUsersFromGroup();
        groups.push_back(group);
        break;
    case 10:
        cout << "Enter post content :" << endl;
        getline(cin, content);
        cin >> content;
        postData.content = content;
        postData.owner = &connect;
        post.post = postData;
        posts.push_back(post);
        break;
    case 11:
        displayAllPost(posts);
        system("PAUSE");
        break;
    case 12:
        cout << "Enter post content you are looking for:" << endl;
        /*getline(cin, content);*/
        cin >> content;
        searchedPost = searchPost(content, posts);
        cout << "Enter comment :";
        cin >> commentContent;
        comment.content = commentContent;
        comment.owner = &connect;
        addComment(searchedPost, comment, posts); // vector 
        displayAllComments(content, posts);
        system("PAUSE");
        break;
    case 13:
        user.displayProfile();
        system("PAUSE");
        break;
    case 14:
        group.getAllUsersFromGroup();
        system("PAUSE");
        break;
    case 15:
        cout << "Enter post content you are looking for:" << endl;
        /*getline(cin, content);*/
        cin >> content;
        post = deletePost(content, posts);
        undo.addDeletedPost(post);
        cout << "SUCCESSFULLY DELETED THE POST " << post.post.content << endl;
        system("PAUSE");
        break;
    case 16:
        posts.push_back(undo.undoPost());
        cout << "SUCCESSFULLY UNDO THE POST " << post.post.content << endl;
        system("PAUSE");
        break;
    case 17:
        if (user.name == "") {
            cout << "You must have account to proceed" << endl;
            goto start;
        }
        getAllUsers(users);
        system("PAUSE");
        cout << "Enter name of the person to unfriend :";
        cin >> name;
        undo.addRemovedFriend(connect.deleteFriend(name));
        cout << "SUCCESSFULLY REMOVED THE FRIEND " << endl;
        system("PAUSE");
        connect.displayAllFriends();
        system("PAUSE");
        break;
    case 18:
        connect.addFriend(undo.undoFriendRequest());
        cout << "SUCCESSFULLY UNDO REMOVED FRIEND " << endl;
        system("PAUSE");
        connect.displayAllFriends();
        system("PAUSE");
        break;
    case 19:
        exit(1);
        break;
    default:
        cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tWRONG OPTION!";
        cout << "\n\n\n\n\n\n\n\n";
        system("PAUSE");
        break;
    }
    goto start;
}

