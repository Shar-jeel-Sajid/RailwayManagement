#pragma once

#include <stdlib.h>
#include <cstring>
#include <string>
#include <sstream>
#include "button.hpp"
#include "backend.cpp"

int find_station(string a, string file_path)
{
    int i = 0;
    ifstream file(file_path);
    string tmp;
    while (getline(file, tmp))
    {
        if (tmp == a)
            return i + 1;
        i++;
    }
    return 0;
}

int to_int(string a)
{
    int num = 0;
    for (int i = 0; i < a.length(); i++)
    {
        num *= 10;
        num += static_cast<int>(a[i] - 48);
    }
    return num;
}

int add_station(RenderWindow& window){
        Font font;
    if (!font.loadFromFile("Font/Times.ttf"))
        cout << "Font Not Loaded here";
    Text text("\0", font);

    /******************************************************************************************************/

    Texture texture;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    Sprite sprite(texture);
    sprite.setPosition(250, 0);

    /******************************************************************************************************/
    Text_box name(Vector2f(110,310),"Name :",text.getFont());
    name.setSize(Vector2f(200,30));
    Input_box name_train(Vector2f(310,310),"",font);
    name_train.setSize(Vector2f(200,30));
    station sta;
    vector<Button> boxes;
    vector<string> all_stations = sta.all_stations();
    for (int i = 0; i < all_stations.size(); i++)
    {
        boxes.push_back(Button(Vector2f(110,350 + i*30),all_stations[i],*text.getFont()));
        boxes[i].setSize(Vector2f(200,30));
    }
    vector <Input_box> length;
    for(int i = 0;i < boxes.size();i++)
    {
        length.push_back(Input_box(Vector2f(310,350 + i*30),"",font));
        length[i].setSize(Vector2f(200,30));
    }
    /*************************************************************/
    Button back(Vector2f(10, 10), "Back", *text.getFont());
    /***************************************************************/
    Texture texture_done;
    texture_done.loadFromFile("Images/done.png");
    Sprite icon_done(texture_done);
    View view(FloatRect(0,0,800,600));
    window.setView(view);
    int scroll_limit = all_stations.size() - 7;
    /******************************************************************************************************/

    Event event;
    Vector2f pos;
    int i = 0, z = 0, y = 0, k = 0, write_cursor = 0;
    int station = 0;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonPressed:
                pos = Vector2f(Mouse::getPosition(window));
                pos.y += ((all_stations.size() - 7) - scroll_limit)*30;
                    write_cursor = 0;
                y = 0;
                if (back.pressed(window, pos))
                {
                    return 0;
                }
                if (icon_done.getGlobalBounds().contains(pos) && k)
                {
                }
                break;
                case Event::MouseWheelMoved:
                if(event.mouseWheel.delta == -1 && (scroll_limit > 0))
                {
                    scroll_limit--;
                    view.move(0,30);
                    window.setView(view);
                }
                if(event.mouseWheel.delta == 1 && (window.getDefaultView().getCenter().y - view.getCenter().y))
                {
                    scroll_limit++;
                    view.move(0,-30);
                    window.setView(view);
                }
                break;
            }
        }
        //     /*****************************************************************************/

        //     /*****************************************************************************/
        for (int i = 0; i < boxes.size(); i++)
            boxes[i].draw(window);
            length[i].draw(window);
        window.draw(sprite);
        back.draw(window);
        /*****************************************************************************/
        name.draw(window);
        window.display();
        window.clear(colors[!ij]);
    }
    return 0;
}

int if_pressed(vector<vector<Button>> boxes, RenderWindow &Window,Vector2f pos)
{
    for (int i = 0; i < boxes.size(); i++)
    {
        for (int j = 0; j < boxes[i].size(); j++)
            if (boxes[i][j].pressed(Window, pos))
            {
                return i + 1;
            }
    }
    return 0;
}

int set_price(RenderWindow& window)
{
    Font font;
    if (!font.loadFromFile("Font/Times.ttf"))
        cout << "Font Not Loaded here";
    Text text("*Station does not exist", font);
    text.setFillColor(colors[ij]);

    /******************************************************************************************************/
    Texture texture;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    Sprite sprite(texture);
    sprite.setPosition(250, 0);
    Button back(Vector2f(10,10),"BACK",*text.getFont());
    /******************************************************************/
    vector<Button> tmpo;
    for(int i = 0;i < 3;i++)
    {
        tmpo.push_back(Button(Vector2f(150,350 +i*30),"BUSINESS CLASS",*text.getFont()));
        tmpo[tmpo.size()-1].setSize(Vector2f(300,30));
    }
    tmpo[2].setText("ECONOMY CLASS");
    tmpo[1].setText("EXECUTIVE CLASS");
    train_business b;
    train_economy ec;
    train_executive ex;
    /******************************************************************************************************/
    vector <Input_box> prices;
    for(int i = 0;i < 3;i++)
    {
        prices.push_back(Input_box(Vector2f(450,350 + i*30),"",font));
        prices[i].setSize(Vector2f(200,30));
    }
    prices[0].setInput(to_string(b.get_price()));
    prices[1].setInput(to_string(ec.get_price()));
    prices[2].setInput(to_string(ex.get_price()));
    /*************************************************************/
    Text_box heading(Vector2f(10, 240), "\t\t\t\t\t\t\t\tSET PRICE", &font);
    heading.setSize(Vector2f(780, 40));
    heading.heading(30);
    Texture icon_done;
    icon_done.loadFromFile("Images/done.png");
    Sprite done(icon_done);
    done.setPosition(651,410);
    /******************************************************************************************************/
    int write_cursor = 0;
    /********************************************************************************************************/
    Event event;
    Vector2f pos;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                exit(0);
                break;
                case Event::MouseButtonPressed:
                pos = Vector2f(Mouse::getPosition(window));
                if(write_cursor)
                    prices[write_cursor - 1].selected(false);
                write_cursor = 0;
                if(back.pressed(window,pos))
                    return 0;
                for(int i = 0;i < 3;i++)
                {
                    if(prices[i].pressed(window,pos))
                    {
                        write_cursor = i + 1;
                        prices[i].selected(true);
                    }
                }
                if(done.getGlobalBounds().contains(pos))
                {
                    b.set_price(to_int(prices[0].get_input()));
                    ec.set_price(to_int(prices[1].get_input()));
                    ex.set_price(to_int(prices[2].get_input()));
                    return 1;
                }
                break;
            }
        }
        /*****************************************************************************/
        /*****************************************************************************/
        for(int i = 0;i < prices.size();i++)
            prices[i].draw(window);
        for(int i = 0;i < 3;i++)
                tmpo[i].draw(window);
        if(write_cursor)
            prices[write_cursor - 1].take_input(window);
        /*****************************************************************************/
        window.draw(done);
        window.draw(sprite);
        window.display();
        window.clear(colors[!ij]);
        heading.draw(window);
        back.draw(window);
    }
}

int select_station(RenderWindow& window,string head)
{
    Font font;
    if (!font.loadFromFile("Font/Times.ttf"))
        cout << "Font Not Loaded here";
    Text text("*Station does not exist", font);
    text.setFillColor(colors[ij]);

    /******************************************************************************************************/
    Texture texture;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    Sprite sprite(texture);
    sprite.setPosition(250, 0);
    Button back(Vector2f(10,10),"BACK",*text.getFont());
    /******************************************************************/
    station sta;
    vector <string> stations = sta.all_stations();
    vector <vector<Button>> boxes;
    vector<Button> tmpo;
    for(int i = 0;i < stations.size();i++)
    {
        tmpo.push_back(Button(Vector2f(100,350 + i*30),to_string(i+1)+".",*text.getFont()));
        tmpo[tmpo.size()-1].setSize(Vector2f(100,30));
        tmpo.push_back(Button(Vector2f(200,350 +i*30),stations[i],*text.getFont()));
        tmpo[tmpo.size()-1].setSize(Vector2f(200,30));
        boxes.push_back(tmpo);
        tmpo.clear();
    }
    /******************************************************************************************************/

    /*************************************************************/
    Text_box heading(Vector2f(10, 240), "\t\t\t\t\t\t"+head, &font);
    heading.setSize(Vector2f(780, 40));
    heading.heading(30);
    Texture icon_done;
    /******************************************************************************************************/
    int write_cursor = 0;
    View view(FloatRect(0,0,800,600));
    window.setView(view);

    int scroll_limit = stations.size() - 7;
    /********************************************************************************************************/
    Event event;
    Vector2f pos;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                exit(0);
                break;
                case Event::MouseButtonPressed:
                    pos = Vector2f(Mouse::getPosition(window));
                    pos.y += ((stations.size() - 7) - scroll_limit)*30;
                if(back.pressed(window,pos))
                    return 0;
                for(int i = 0;i < boxes.size();i++)
                    return if_pressed(boxes,window,pos);
                break;
                case Event::MouseWheelMoved:
                if(event.mouseWheel.delta == -1 && (scroll_limit > 0))
                {
                    scroll_limit--;
                    view.move(0,30);
                    window.setView(view);
                }
                if(event.mouseWheel.delta == 1 && (window.getDefaultView().getCenter().y - view.getCenter().y))
                {
                    scroll_limit++;
                    view.move(0,-30);
                    window.setView(view);
                }
                break;
            }
        }
        /*****************************************************************************/
        /*****************************************************************************/
        for(int i = 0;i < boxes.size();i++)
            for(int j = 0;j < boxes[i].size();j++)
                boxes[i][j].draw(window);
        /*****************************************************************************/
        window.draw(sprite);
        window.display();
        window.clear(colors[!ij]);
        heading.draw(window);
        back.draw(window);
    }
}

int select_class(RenderWindow& window,string head)
{
    Font font;
    if (!font.loadFromFile("Font/Times.ttf"))
        cout << "Font Not Loaded here";
    Text text("*Station does not exist", font);
    text.setFillColor(colors[ij]);

    /******************************************************************************************************/
    Texture texture;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    Sprite sprite(texture);
    sprite.setPosition(250, 0);
    Button back(Vector2f(10,10),"BACK",*text.getFont());
    /******************************************************************/
    vector<Button> tmpo;
    for(int i = 0;i < 3;i++)
    {
        tmpo.push_back(Button(Vector2f(200,350 +i*30),"BUSINESS CLASS",*text.getFont()));
        tmpo[tmpo.size()-1].setSize(Vector2f(300,30));
    }
    tmpo[2].setText("ECONOMY CLASS");
    tmpo[1].setText("EXECUTIVE CLASS");
    /******************************************************************************************************/

    /*************************************************************/
    Text_box heading(Vector2f(10, 240), "\t\t\t\t\t\t\t\t"+head, &font);
    heading.setSize(Vector2f(780, 40));
    heading.heading(30);
    Texture icon_done;
    /******************************************************************************************************/
    int write_cursor = 0;
    /********************************************************************************************************/
    Event event;
    Vector2f pos;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                exit(0);
                break;
                case Event::MouseButtonPressed:
                    pos = Vector2f(Mouse::getPosition(window));
                if(back.pressed(window,pos))
                    return 0;
                for(int i = 0;i < 3;i++)
                    if(tmpo[i].pressed(window,pos))
                        return i + 1;
                break;
            }
        }
        /*****************************************************************************/
        /*****************************************************************************/
        for(int i = 0;i < 3;i++)
                tmpo[i].draw(window);
        /*****************************************************************************/
        window.draw(sprite);
        window.display();
        window.clear(colors[!ij]);
        heading.draw(window);
        back.draw(window);
    }
}

vector <Text_box> available_trains(vector <train_business> all_trains,const Font* font)
{
    vector <Text_box> trains;
    for(int i = 0;i < all_trains.size();i++)
    {
        trains.push_back(Text_box(Vector2f(300,443+(i*31)),all_trains[i].get_name(),font));
        trains[i].setSize(Vector2f(200,30));
    }
    return trains;
}

int  booking(users* user,RenderWindow& window){
    Font font;
    if (!font.loadFromFile("Font/Times.ttf"))
        cout << "Font Not Loaded here";
    Text text("\tSELECT TRAIN", font);
    text.setPosition(250,280);
    text.setCharacterSize(30);
    text.setStyle(Text::Bold);
    text.setFillColor(colors[ij]);

    /******************************************************************************************************/
    Texture texture;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    Sprite sprite(texture);
    sprite.setPosition(250, 0);
    Button back(Vector2f(10,10),"BACK",*text.getFont());
    /******************************************************************************************************/
    int ending ,starting = select_station(window,"SELECT BOARDING STATION");
    if(starting){
        if(!(ending = select_station(window,"SELECT EXIT STATION")))
            return 0;
    }
    else
        return 0;
    cout << "0";
    /*************************************************************/
    /******************************************************************/
    passanger_booking p;int write_cursor;
    vector <int> price;
    vector <train_business> tmp = p.get_train(starting,ending);
    vector <Button> all_trains;
    vector <Button> prices;
    if(tmp.size())
    for(int i = 0;i < tmp.size();i++)
    {
        all_trains.push_back(Button(Vector2f(200,350 + i*30),tmp[i].get_name(),*text.getFont()));
        all_trains[i].setSize(Vector2f(200,30));
    }
    else
    {
        all_trains.push_back(Button(Vector2f(200,350),"NO TRAINS AVAILABLE",*text.getFont()));
        all_trains[0].setSize(Vector2f(200,30));
    }
    for(int i = 0 ;i < tmp.size();i++)
    {
        if(tmp[i].get_id()=="Business"){
            price.push_back(tmp[i].get_price());
        }
        if(tmp[i].get_id()=="Economy"){
            train_economy ll;
            price.push_back(ll.get_price());
        }
        if(tmp[i].get_id()=="Executive"){
            train_executive jj;
            price.push_back(jj.get_price());
        }
    }
    for(int i = 0;i < price.size();i++)
    {
        prices.push_back(Button(Vector2f(400,350 + i*30),to_string(price[i]),*text.getFont()));
        cout << to_string(price[i]);
        prices[i].setSize(Vector2f(200,30));
    }
    Input_box no_of_tickets(Input_box(Vector2f(300,320),"NO OF TICKETS : ", font)); 
    no_of_tickets.setSize(Vector2f(200,30));
    no_of_tickets.setInput("1");
    /******************************************************************************************************/
    /********************************************************************************************************/
    Event event;
    Vector2f pos;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                exit(0);
                break;
                case Event::MouseButtonPressed:
                    write_cursor = 0;
                    no_of_tickets.selected(false);
                    pos = Vector2f(Mouse::getPosition(window));
                    if(back.pressed(window,pos))
                        return 0;
                    for(int i = 0;i < all_trains.size();i++)
                    {
                        if(all_trains[i].pressed(window,pos))
                        {
                            if(tmp.size())
                                p.set_data(user->get_name(),tmp[i].get_name(),starting,ending,rand()%300 +1);
                            return 0;
                        }
                    }
                    if(no_of_tickets.pressed(window,pos))
                    {
                        write_cursor = 1;
                        no_of_tickets.selected(true);
                    }
                break;
            }
        }
        /*****************************************************************************/
        if(write_cursor)
            no_of_tickets.take_input(window);
        for(int i = 0;i < prices.size();i++)
        {
            prices[i].setText(to_string(price[i]*(to_int(no_of_tickets.get_input()))));
            prices[i].draw(window);
        }
        /*****************************************************************************/
        for(int i = 0;i < all_trains.size();i++)
            all_trains[i].draw(window);
        /*****************************************************************************/
        no_of_tickets.draw(window);
        window.draw(sprite);
        window.draw(text);
        window.display();
        window.clear(colors[!ij]);
        back.draw(window);
    }   
}

int cancel_booking(users* user , RenderWindow& window)
{
    Font font;
    if (!font.loadFromFile("Font/Times.ttf"))
        cout << "Font Not Loaded here";
    Text text("*Station does not exist", font);

    /******************************************************************************************************/
    vector <string> all_tickets;
    int default_pos = 0;
    Texture texture;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    Sprite sprite(texture);
    sprite.setPosition(250, 0);
    train_business all;
    vector<train_business> train=all.all_trains();
    Button back(Vector2f(10,10),"BACK",*text.getFont());
    /******************************************************************/
    passanger_booking p;
    vector <vector<string>> tickets = p.get_data(user->get_name());
    /******************************************************************************************************/
    vector <vector<Button>> boxes;
    vector <Button> tmp;
    for(int i = 0;i < tickets.size();i ++)
    {
        tmp.push_back(Text_box(Vector2f(10,350+i*30),tickets[i][5].substr(0,4),text.getFont()));
        tmp[0].setSize(Vector2f(120,30));
        tmp.push_back(Text_box(Vector2f(300,350+i*30),tickets[i][1],text.getFont()));
        tmp[1].setSize(Vector2f(170,30));
        tmp.push_back(Text_box(Vector2f(470,350+i*30),tickets[i][2],text.getFont()));
        tmp[2].setSize(Vector2f(190,30));
        tmp.push_back(Text_box(Vector2f(130,350+i*30),tickets[i][3],text.getFont()));
        tmp[3].setSize(Vector2f(170,30));
        tmp.push_back(Text_box(Vector2f(660,350+i*30),tickets[i][4],text.getFont()));
        tmp[4].setSize(Vector2f(100,30));
        boxes.push_back(tmp);
        tmp.clear();
    }
        tmp.push_back(Text_box(Vector2f(10,310),"TYPE",text.getFont()));
        tmp[0].setSize(Vector2f(120,30));
        tmp.push_back(Text_box(Vector2f(300,310),"START",text.getFont()));
        tmp[1].setSize(Vector2f(170,30));
        tmp.push_back(Text_box(Vector2f(470,310),"END",text.getFont()));
        tmp[2].setSize(Vector2f(190,30));
        tmp.push_back(Text_box(Vector2f(130,310),"TRAIN",text.getFont()));
        tmp[3].setSize(Vector2f(170,30));
        tmp.push_back(Text_box(Vector2f(660,310),"SEAT",text.getFont()));
        tmp[4].setSize(Vector2f(100,30));
    /*************************************************************/
    Text_box heading(Vector2f(10, 240), "\t\t\t\t\t\t\t\tCANCEL TICKETS", &font);
    heading.setSize(Vector2f(780, 40));
    heading.heading(30);
    /******************************************************************************************************/
    Texture del_icon;
    del_icon.loadFromFile("Images/delete.png");
    Sprite icon_del(del_icon);
    /********************************************************************************************************/
    View view(FloatRect(0,0,800,600));
    window.setView(view);
    Event event;
    Vector2f pos;
    int press = 0,scroll_limit = tickets.size() - 8;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                exit(0);
                break;
                case Event::MouseButtonPressed:
                    pos = Vector2f(Mouse::getPosition(window));
                if(back.pressed(window,pos))
                    return 0;
                if(press && icon_del.getGlobalBounds().contains(pos))
                {
                    p.cancel_booking(tickets[press - 1]);
                    return 1;
                }
                if(press = if_pressed(boxes,window,pos))
                {
                    icon_del.setPosition(761,350 + (press-1)*30);
                }
                break;
            case Event::MouseWheelMoved:
                if(event.mouseWheel.delta == -1 && (scroll_limit > 0))
                {
                    scroll_limit--;
                    view.move(0,30);
                    window.setView(view);
                }
                if(event.mouseWheel.delta == 1 && (window.getDefaultView().getCenter().y - view.getCenter().y))
                {
                    scroll_limit++;
                    view.move(0,-30);
                    window.setView(view);
                }
                break;
            }
        }
        /*****************************************************************************/
        /*****************************************************************************/
        for(int i = 0;i < boxes.size();i ++)
        {
            for(int j = 0;j < boxes[i].size();j++)
            boxes[i][j].draw(window);
        }
        if(press)
            window.draw(icon_del);
        for(int i =0;i < 5;i++)
            tmp[i].draw(window);
        /*****************************************************************************/
        window.draw(sprite);
        window.display();
        window.clear(colors[!ij]);
        heading.draw(window);
        back.draw(window);
    }
}

void user_page(users* user,RenderWindow &window)
{
    Font font;
    if (!font.loadFromFile("Font/Times.ttf"))
        cout << "Font Not Loaded here";
    Text text("\0", font);

    /******************************************************************************************************/

    Texture texture;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    Sprite sprite(texture);
    sprite.setPosition(250, 0);
    vector<trains> train;


    /******************************************************************************************************/
    vector <Texture> icon (2);
    icon[0].loadFromFile("Images/book_tickets.png");
    icon[1].loadFromFile("Images/cancel_tickets.png");
    vector <Sprite> icons;
    for(int i = 0;i < 2;i++)
        icons.push_back(Sprite(icon[i]));
    icons[0].setPosition(Vector2f(250,300));
    icons[1].setPosition(Vector2f(250,450));
    /*************************************************************/
    Text_box heading(Vector2f(10, 240), "\t\t\t\t\t\t\t\tUSER ACCOUNT", &font);
    heading.setSize(Vector2f(780, 40));
    heading.heading(30);
    /******************************************************************************************************/
    /********************************************************************************************************/
    Event event;
    Vector2f pos;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
                case Event::MouseButtonPressed:
                    pos = Vector2f(Mouse::getPosition(window));
                    if(icons[0].getGlobalBounds().contains(pos))
                        while(true)
                        {
                            if(!booking(user,window))
                            {
                                break;
                            }
                        }
                    if(icons[1].getGlobalBounds().contains(pos))
                    {
                        while(true)
                        {
                            if(!cancel_booking(user,window))
                            {
                                break;
                            }
                        }
                    }
            }
        }
            /*****************************************************************************/
            /*****************************************************************************/
        /*****************************************************************************/
        for(int i = 0;i < icons.size();i++)
            window.draw(icons[i]);
        window.draw(sprite);
        window.display();
        window.clear(colors[!ij]);
        heading.draw(window);
    }
}

int Login_page(RenderWindow &window)
{
    
    invert_colors(ij);
    Font font;
    if (!font.loadFromFile("Font/Times.ttf"))
        cout << "Font Not Loaded";
    Text text("*Incorrect Username Or Password", font, 15);
    text.setFillColor(Color::Red);
    text.setPosition(Vector2f(290, 420));
    /******************************************************************************************************/

    Texture texture, hide_icon, show_icon;
    texture.loadFromFile("Images/Icon"+to_string(ij)+ ".png");
    hide_icon.loadFromFile("Images/hide_icon.png");
    show_icon.loadFromFile("Images/show_icon.png");
    Sprite sprite(texture), Hide(hide_icon);
    Hide.setPosition(Vector2f(520, 320));
    sprite.setPosition(250, 0);
    Texture invert;
    invert.loadFromFile("Images/invert"+to_string(ij)+".png");
    Sprite icon_invert(invert);
    icon_invert.setPosition(760,10);

    /******************************************************************************************************/
    int write_cursor = 0;
    vector<Button> buttons;
    vector<Input_box> boxes;
    buttons.push_back(Button(Vector2f(290, 370), "SignIn", font));
    buttons.push_back(Button(Vector2f(420, 370), "New", font));
    buttons.push_back(Button(Vector2f(520, 320), "\0", font));
    buttons[2].setSize(Vector2f(30, 30));
    boxes.push_back(Input_box(Vector2f(250, 270), "User Name", font));
    boxes.push_back(Input_box(Vector2f(250, 320), "Password", font));
    boxes[1].show_pass();
    boxes[1].setSize(Vector2f(270, 30));
    /******************************************************************************************************/

    Event event;
    Vector2f pos;
    bool incorrect = false;
    int Hide_pass = 0;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                cout << boxes[0].get_input();
                break;
            case Event::MouseButtonPressed:
                pos = Vector2f(Mouse::getPosition(window));
                if (write_cursor)
                    boxes.at(write_cursor - 1).selected(false);
                for (int i = 0; i < boxes.size(); i++)
                {
                    if (boxes[i].pressed(window, pos))
                    {
                        boxes[i].selected(true);
                        write_cursor = i + 1;
                        break;
                    }
                    if (i == boxes.size() - 1)
                    {
                        write_cursor = 0;
                    }
                }
                if (buttons[2].pressed(window, pos))
                {
                    boxes[1].show_pass();
                    switch (Hide_pass)
                    {
                    case 0:
                        Hide.setTexture(show_icon);
                        Hide_pass++;
                        break;

                    default:
                        Hide.setTexture(hide_icon);
                        Hide_pass--;
                        break;
                    }
                }
                if (buttons[0].pressed(window, pos))
                {
                    users *ptr = login_page(boxes[0].get_input(), boxes[1].get_input());
                    if (ptr == nullptr)
                    {
                        incorrect = true;
                        for (int i = 0; i < boxes.size(); i++)
                            boxes[i].clear();
                    }
                    else if (ptr->if_admin())
                    {
                        admin_page(window);
                        return 0;
                    }
                    else
                    {
                        user_page(ptr,window);
                        return 0;
                    }
                }
                if (buttons[1].pressed(window, pos))
                {
                    new_page(window);
                    return 0;
                }
                if(icon_invert.getGlobalBounds().contains(pos))
                    {invert_colors(!ij);
                    return 1;}
                break;
            default:
                break;
            }
        }
        /*****************************************************************************/
        if (write_cursor)
        {
            boxes[write_cursor - 1].take_input(window);
        }
        /*****************************************************************************/
        for (int i = 0; i < buttons.size(); i++)
            buttons[i].draw(window);
        for (int i = 0; i < boxes.size(); i++)
            boxes[i].draw(window);
        window.draw(sprite);
        if (incorrect)
            window.draw(text);
        window.draw(Hide);
        window.draw(icon_invert);
        /*****************************************************************************/

        window.display();
        window.clear(colors[!ij]);
    }
    return 0;
}

void new_page(RenderWindow &window)
{
    Font font;
    if (!font.loadFromFile("Font/Times.ttf"))
        cout << "Font Not Loaded";
    Text text("*Password Not Matched", font, 15);
    text.setFillColor(Color::Red);
    text.setPosition(Vector2f(290, 460));
    /******************************************************************************************************/

    Texture texture, hide_icon, show_icon;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    hide_icon.loadFromFile("Images/hide_icon.png");
    show_icon.loadFromFile("Images/show_icon.png");
    Sprite sprite(texture), Hide1(hide_icon), Hide2(hide_icon);
    Hide1.setPosition(Vector2f(520, 320));
    Hide2.setPosition(Vector2f(520, 370));
    sprite.setPosition(250, 0);
    /******************************************************************************************************/
    int write_cursor = 0;
    vector<Button> buttons;
    vector<Input_box> boxes;
    buttons.push_back(Button(Vector2f(340, 420), "Create", font));
    buttons.push_back(Button(Vector2f(520, 320), "\0", font));
    buttons[1].setSize(Vector2f(30, 30));
    buttons.push_back(Button(Vector2f(520, 370), "\0", font));
    buttons[2].setSize(Vector2f(30, 30));
    boxes.push_back(Input_box(Vector2f(250, 270), "User Name", font));
    boxes.push_back(Input_box(Vector2f(250, 320), "Password", font));
    boxes.push_back(Input_box(Vector2f(250, 370), "Confirm", font));
    boxes[2].show_pass();
    boxes[1].show_pass();
    boxes[1].setSize(Vector2f(270, 30));
    boxes[2].setSize(Vector2f(270, 30));
    /******************************************************************************************************/

    Event event;
    Vector2f pos;
    int hide1, hide2 = hide1 = 0;
    bool incorrect = false;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonPressed:
                pos = Vector2f(Mouse::getPosition(window));
                if (write_cursor)
                    boxes.at(write_cursor - 1).selected(false);
                for (int i = 0; i < boxes.size(); i++)
                {
                    if (boxes[i].pressed(window, pos))
                    {
                        boxes[i].selected(true);
                        write_cursor = i + 1;
                        break;
                    }
                    if (i == boxes.size() - 1)
                    {
                        write_cursor = 0;
                    }
                }
                if (buttons[1].pressed(window, pos))
                {
                    boxes[1].show_pass();
                    switch (hide1)
                    {
                    case 0:
                        Hide1.setTexture(show_icon);
                        hide1++;
                        break;

                    default:
                        Hide1.setTexture(hide_icon);
                        hide1--;
                        break;
                    }
                }
                if (buttons[2].pressed(window, pos))
                {
                    boxes[2].show_pass();
                    switch (hide2)
                    {
                    case 0:
                        Hide2.setTexture(show_icon);
                        hide2++;
                        break;

                    default:
                        Hide2.setTexture(hide_icon);
                        hide2--;
                        break;
                    }
                }
                if (buttons[0].pressed(window, pos))
                {
                    if (boxes[1].get_input() != boxes[2].get_input() || boxes[1].get_input().empty() || boxes[0].get_input().empty())
                        incorrect = true;
                    else
                    {
                        user_page(new_user(boxes[0].get_input(), boxes[1].get_input()),window);
                        return;
                    }
                }
                break;
            default:
                break;
            }
        }
        /*****************************************************************************/
        if (write_cursor)
        {
            boxes[write_cursor - 1].take_input(window);
        }
        /*****************************************************************************/
        for (int i = 0; i < buttons.size(); i++)
            buttons[i].draw(window);
        for (int i = 0; i < boxes.size(); i++)
            boxes[i].draw(window);
        window.draw(sprite);
        if (incorrect)
            window.draw(text);
        window.draw(Hide1);
        window.draw(Hide2);
        /*****************************************************************************/

        window.display();
        window.clear(colors[!ij]);
    }
}

void admin_page(RenderWindow &window)
{
    Font font;
    if (!font.loadFromFile("Font/Times.ttf"))
        cout << "Font Not Loaded here";
    Text text("\0", font);

    /******************************************************************************************************/

    Texture texture;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    Sprite sprite(texture);
    sprite.setPosition(250, 0);

    /******************************************************************************************************/

    vector<Text_box> boxes;
    boxes.push_back(Text_box(Vector2f(10, 240), "\t\t\t\t\t\t\t    ADMIN PANEL", text.getFont()));
    boxes[0].setSize(Vector2f(780, 40));
    boxes[0].heading(30);

    /*************************************************************/
    vector<Button> buttons;
    for (int i = 0; i < 5; i++)
    {
        buttons.push_back(Button(Vector2f(250, 330 + (i * 30)), "", *text.getFont()));
        buttons[i].setSize(Vector2f(300, 30));
        buttons[i].highlight();
    }
    buttons[0].setText("Stations");
    buttons[1].setText("Tracks");
    buttons[2].setText("Trains");
    buttons[3].setText("Schedule");
    buttons[4].setText("Set Price");
    /******************************************************************************************************/

    Event event;
    Vector2f pos;
    int i = 0;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonPressed:
                pos = Vector2f(Mouse::getPosition(window));
                for (i = 0; i < buttons.size(); i++)
                    if (buttons[i].pressed(window, pos))
                        break;
                switch (i)
                {
                case 0:while(1)
                    {
                        if(!station_page(window))
                            break;
                    }break;
                case 1:
                    while (true)
                    {
                        if (!track_page(window))
                            break;
                    }
                    break;
                case 2:
                    while (true)
                    {
                        if (!train_page(window))
                            break;
                    }
                    break;
                case 3:
                    manage_schedule(window);
                    break;
                case 4:
                    set_price(window);
                    break;
                }
                break;
            }
        }
        for (int i = 0; i < boxes.size(); i++)
            boxes[i].draw(window);
        window.draw(sprite);
        for (int i = 0; i < buttons.size(); i++)
            buttons[i].draw(window);
        //     /*****************************************************************************/

        window.display();
        window.clear(colors[!ij]);
    }
}

void set_Stations(vector<Text_box> &boxes, const Font *font)
{
    station sta;
    boxes.push_back(Text_box(Vector2f(10, 240), "\t\t\t\t\t\t\t   MANAGE STATIONS", font));
    boxes[0].setSize(Vector2f(780, 40));
    boxes[0].heading(30);
    char c;
    string tmp;
    vector<string> Stations = sta.all_stations();
    for (int i = 0; i < Stations.size(); i++)
    {
        tmp.clear();
        c = i + 1 + 48;
        tmp += c;
        tmp += ".  ";
        boxes.push_back(Text_box(Vector2f(10, 350 + (i * 30)), tmp, font));
        boxes[boxes.size() - 1].setSize(Vector2f(80, 30));
        boxes.push_back(Text_box(Vector2f(90, 350 + (i * 30)), Stations[i], font));
        boxes[boxes.size() - 1].setSize(Vector2f(200, 30));
    }
}

int station_page(RenderWindow &window)
{
    Font font;
    if (!font.loadFromFile("Font/Times.ttf"))
        cout << "Font Not Loaded here";
    Text text("\0", font);

    /******************************************************************************************************/

    Texture texture;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    Sprite sprite(texture);
    sprite.setPosition(250, 0);

    /******************************************************************************************************/
    Text_box name(Vector2f(110,310),"Name",text.getFont());
    name.setSize(Vector2f(200,30));
    station sta;
    vector<Button> boxes;
    vector<string> all_stations = sta.all_stations();
    for (int i = 0; i < all_stations.size(); i++)
    {
        boxes.push_back(Button(Vector2f(110,350 + i*30),all_stations[i],*text.getFont()));
        boxes[i].setSize(Vector2f(200,30));
    }
    
    /*************************************************************/
    Button back(Vector2f(10, 10), "Back", *text.getFont());
    Button add(Vector2f(110, 350 + (boxes.size()* 30)), "ADD", *text.getFont());
    Input_box box(Vector2f(110, 350 + (boxes.size()* 30)),"", font);
    box.setSize(Vector2f(200, 30));
    /***************************************************************/
    Texture texture_del, texture_done;
    texture_done.loadFromFile("Images/done.png");
    texture_del.loadFromFile("Images/delete.png");
    Sprite icon_delete(texture_del), icon_done(texture_done);
    View view(FloatRect(0,0,800,600));
    window.setView(view);
    int scroll_limit = all_stations.size() - 7;
    /******************************************************************************************************/

    Event event;
    Vector2f pos;
    int i = 0, z = 0, y = 0, k = 0, write_cursor = 0;
    int station = 0;
    // bool incorrect = false;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonPressed:
                pos = Vector2f(Mouse::getPosition(window));
                pos.y += ((all_stations.size() - 7) - scroll_limit)*30;
                    write_cursor = 0;
                    box.selected(false);
                if (icon_delete.getGlobalBounds().contains(pos) && y)
                {
                    sta.remove_station(all_stations[y-1]);
                    return 1;
                }
                y = 0;
                for (int i = 0; i < boxes.size(); i++)
                {
                    if (boxes[i].pressed(window, pos) &&!k)
                    {
                        y = i + 1;
                        icon_delete.setPosition(Vector2f(311,350 + i*30));
                        break;
                    }
                }
                if (back.pressed(window, pos))
                {
                    return 0;
                }
                if (add.pressed(window, pos))
                {
                    k = 1;
                    icon_done.setPosition(Vector2f(311, 350 + (boxes.size()*30)));
                }
                if (box.pressed(window, pos) && k)
                {
                    write_cursor = 1;
                    box.selected(true);
                }
                if (icon_done.getGlobalBounds().contains(pos) && k)
                {
                    if(!box.get_input().empty())
                    {
                        sta.set_data(box.get_input());
                        return 1;
                    }
                }
                break;
                case Event::MouseWheelMoved:
                if(event.mouseWheel.delta == -1 && (scroll_limit > 0))
                {
                    scroll_limit--;
                    view.move(0,30);
                    window.setView(view);
                }
                if(event.mouseWheel.delta == 1 && (window.getDefaultView().getCenter().y - view.getCenter().y))
                {
                    scroll_limit++;
                    view.move(0,-30);
                    window.setView(view);
                }
                break;
            }
        }
        //     /*****************************************************************************/
        if (write_cursor)
        {
            box.take_input(window);
        }
        //     /*****************************************************************************/
        for (int i = 0; i < boxes.size(); i++)
            boxes[i].draw(window);
        window.draw(sprite);
        back.draw(window);
        if(y)
            window.draw(icon_delete);
        switch (k)
        {
        case 0:
            add.draw(window);
            break;
        case 1:
            box.draw(window);
            window.draw(icon_done);
            break;
        }
        /*****************************************************************************/
        name.draw(window);
        window.display();
        window.clear(colors[!ij]);
    }
    return 0;
}



int track_page(RenderWindow &window)
{
    Font font;
    font.loadFromFile("Font/arial.ttf");
    Text text("MANAGE TRACKS", font);
    text.setCharacterSize(30);
    text.setPosition(Vector2f(300, 240));

    /******************************************************************************************************/
    vector <Text_box> names;
    for(int i = 0;i < 3;i++)
    {
        names.push_back(Text_box(Vector2f(90 +i*200,310),"",text.getFont()));
        names[i].setSize(Vector2f(200,30));
    }
    names[0].setText("START");
    names[1].setText("END");
    names[2].setText("LENGTH");
    Texture texture;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    Sprite sprite(texture);
    sprite.setPosition(250, 0);
    Text_box heading(Vector2f(10, 240), "\t\t\t\t\t\t\t\t\t\t\tMANAGE TRACKS", &font);
    heading.setSize(Vector2f(780, 40));
    /******************************************************************************************************/
    station track;
    vector<station> all_track = track.all_tracks();
    vector<vector<Button>> boxes;
    vector<string> tmpo;
    float a;
    vector<Button> tmp;
    for (int i = 0; i < all_track.size(); i++)
    {
        tmpo = all_track[i].get_data();
        a=stof(tmpo[2]);
        stringstream aa;
        aa<<a;
        tmpo[2]=aa.str();
        // tmpo[2]=to_string(a);
        tmp.push_back(Text_box(Vector2f(10, 350 + (i * 30)), to_string(i + 1) + ".", text.getFont()));
        (*(tmp.end() - 1)).setSize(Vector2f(80, 30));
        tmp.push_back(Text_box(Vector2f(90, 350 + (i * 30)), tmpo[0], text.getFont()));
        (*(tmp.end() - 1)).setSize(Vector2f(200, 30));
        tmp.push_back(Text_box(Vector2f(290, 350 + (i * 30)), tmpo[1], text.getFont()));
        (*(tmp.end() - 1)).setSize(Vector2f(200, 30));
        tmp.push_back(Text_box(Vector2f(490, 350 + (i * 30)), tmpo[2], text.getFont()));
        (*(tmp.end() - 1)).setSize(Vector2f(200, 30));
        (boxes).push_back(tmp);
        tmpo.clear();
        tmp.clear();
    }
    /*************************************************************/
    Button back(Vector2f(10, 10), "Back", *text.getFont());
    Button add(Vector2f(10, 350 + (boxes.size() * 30)), "ADD", *text.getFont());
    Input_box get_len(Input_box(Vector2f(490,350 + (boxes.size())*30),"",font));
    get_len.setSize(Vector2f(200,30));
    /***************************************************************/
    Texture texture_del, texture_done;
    texture_done.loadFromFile("Images/done.png");
    texture_del.loadFromFile("Images/delete.png");
    Sprite icon_delete(texture_del), icon_done(texture_done);
    icon_done.setPosition(Vector2f(691,350+boxes.size()*30));
    /******************************************************************************************************/

    Event event;
    Vector2f pos;
    string in3;
    int i = 0, z = 0, y = 0, k = 0, write_cursor = 0, in1, in2 = in2 = in1 = 0;
    int track_num = 0;
    View view(FloatRect(0,0,800,600));
    window.setView(view);
    int scroll_limit = all_track.size() - 7;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                exit(0);
                break;
            case Event::MouseButtonPressed:
                pos = Vector2f(Mouse::getPosition(window));
                pos.y += ((all_track.size() - 7) - scroll_limit)*30;
                get_len.selected(false);
                if (icon_delete.getGlobalBounds().contains(pos) && track_num && !write_cursor)
                {
                    track.remove_track(track_num - 1);
                    add.setPositon(Vector2f(10,350+(boxes.size()-1)*30));
                    return 1;
                }
                write_cursor = 0;
                if (back.pressed(window, pos))
                {
                    return 0;
                }
                track_num = if_pressed(boxes, window, pos);
                if (add.pressed(window, pos))
                {
                    in1 = select_station(window,"Select Starting Station");
                    in2 = select_station(window,"Select Ending Station");
                    if(in1==in2){
                        return 1;
                    }
                    k = 1;
                }
                if (icon_done.getGlobalBounds().contains(pos) && !in3.empty())
                {
                    tracks*z=static_cast<tracks*>(&track);
                    z->set_data(in1,in2,in3);
                    return 1;
                }
                if(k && get_len.pressed(window,pos))
                {
                    write_cursor = 1;
                }
                break;
                case Event::MouseWheelMoved:
                if(event.mouseWheel.delta == -1 && (scroll_limit > 0))
                {
                    scroll_limit--;
                    view.move(0,30);
                    window.setView(view);
                }
                if(event.mouseWheel.delta == 1 && (window.getDefaultView().getCenter().y - view.getCenter().y))
                {
                    scroll_limit++;
                    view.move(0,-30);
                    window.setView(view);
                }
                break;
            }
        }
        /*****************************************************************************/
        //     /*****************************************************************************/
        if (track_num)
        {
            icon_delete.setPosition(Vector2f(691, (350 + ((track_num - 1) * 30))));
            window.draw(icon_delete);
        }
        if(write_cursor)
        {
            get_len.selected(true);
            get_len.take_input(window);
            in3 = get_len.get_input();
            window.draw(icon_done);
        }
        if(k)
            get_len.draw(window);
        window.draw(sprite);

        for (int i = 0; i < (boxes).size(); i++)
        {
            for (int j = 0; j < boxes[0].size(); j++)
                (boxes)[i][j].draw(window);
        }
        back.draw(window);
        add.draw(window);
        for(int i =0;i < 3;i++)
            names[i].draw(window);
        /*****************************************************************************/
        heading.draw(window);
        window.display();
        window.clear(colors[!ij]);
    }
}

int train_page(RenderWindow &window)
{
    Font font;
    font.loadFromFile("Font/arial.ttf");
    Text text("MANAGE TRACKS", font);

    /******************************************************************************************************/
    Text_box name1(Vector2f(10,310),"TYPE",text.getFont()),name(Vector2f(210,310),"NAME",text.getFont());
    name.setSize(Vector2f(200,30));name1.setSize(Vector2f(200,30));
    Texture texture;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    Sprite sprite(texture);
    sprite.setPosition(250, 0);
    Text_box heading(Vector2f(10, 240), "\t\t\t\t\t\t\t\t\t\t\tMANAGE TRAINS", &font);
    heading.setSize(Vector2f(780, 40));
    /******************************************************************************************************/
    train_business train;
    vector<train_business> all_train = train.all_trains();
    vector<vector<Button>> boxes;
    vector<string> tmpo;
    vector<Button> tmp;
    for (int i = 0; i < all_train.size(); i++)
    {
        tmpo = all_train[i].get_data();
        tmp.push_back(Text_box(Vector2f(10, 350 + (i * 30)), tmpo[0], text.getFont()));
        (*(tmp.end() - 1)).setSize(Vector2f(200, 30));
        tmp.push_back(Text_box(Vector2f(210, 350 + (i * 30)), tmpo[1], text.getFont()));
        (*(tmp.end() - 1)).setSize(Vector2f(200, 30));
        (boxes).push_back(tmp);
        tmpo.clear();
        tmp.clear();
    }
    /*************************************************************/
    Button back(Vector2f(10, 10), "Back", *text.getFont());
    Button add(Vector2f(10, 350 + (boxes.size() * 30)), "ADD", *text.getFont());

    vector<Input_box> box;
    box.push_back(Input_box(Vector2f(210, 350 + (boxes.size() * 30)), static_cast<string>(" "), font));
    box[box.size() - 1].setSize(Vector2f(200, 30));
    // // /***************************************************************/
    Texture texture_del, texture_done;
    texture_done.loadFromFile("Images/done.png");
    texture_del.loadFromFile("Images/delete.png");
    Sprite icon_delete(texture_del), icon_done(texture_done);
    // /******************************************************************************************************/

    Event event;
    Vector2f pos;
    int i = 0, z = 0, y = 0, k = 0, write_cursor = 0,in1 = 0;
    int train_num = 0;
    View view(FloatRect(0,0,800,600));
    window.setView(view);
    int scroll_limit = all_train.size() - 7;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                exit(0);///########################################################
                break;
            case Event::MouseButtonPressed:
                pos = Vector2f(Mouse::getPosition(window));
                pos.y += ((all_train.size() - 7) - scroll_limit)*30;
                if (write_cursor)
                {
                    write_cursor--;
                }
                for (int i = 0; i < box.size(); i++)
                    box[i].selected(false);
                if (icon_delete.getGlobalBounds().contains(pos) && train_num)
                {
                    train.remove_train(train_num);
                    return 1;
                }
                if (back.pressed(window, pos))
                {
                    return 0;
                }
                train_num = if_pressed(boxes, window,pos);
                if (add.pressed(window, pos))
                {
                    in1 = select_class(window,"SELECT CLASS");
                    k = 1;
                    icon_done.setPosition(Vector2f(411, 350 + (boxes.size() * 30)));
                }
                if (k)
                    for (int i = 0; i < box.size(); i++)
                        if (box[i].pressed(window, pos))
                        {
                            write_cursor = 1;
                            box[i].selected(true);
                        }
                if (icon_done.getGlobalBounds().contains(pos) && k)
                {
                    cout << in1;
                    if (in1 && !box[0].get_input().empty())
                    {
                        cout << in1;
                        train.set_data(in1,box[0].get_input());
                    }
                    return 1;
                }
                break;
                case Event::MouseWheelMoved:
                if(event.mouseWheel.delta == -1 && (scroll_limit > 0))
                {
                    scroll_limit--;
                    view.move(0,30);
                    window.setView(view);
                }
                if(event.mouseWheel.delta == 1 && (window.getDefaultView().getCenter().y - view.getCenter().y))
                {
                    scroll_limit++;
                    view.move(0,-30);
                    window.setView(view);
                }
                break;
            }
        }
        //         /*****************************************************************************/
        if (write_cursor)
        {
            for (int i = 0; i < box.size(); i++)
                if (box[i].pressed(window, pos))
                    box[i].take_input(window);
        }
        //     //     /*****************************************************************************/
        if (train_num)
        {
            icon_delete.setPosition(Vector2f(411, (350 + ((train_num - 1) * 30))));
            window.draw(icon_delete);
        }
        window.draw(sprite);
        switch (k)
        {
        case 0:
            add.draw(window);
            break;
        case 1:
            for (int i = 0; i < box.size(); i++)
                box[i].draw(window);
            window.draw(icon_done);
            break;
        }
        for (int i = 0; i < (boxes).size(); i++)
        {
            for (int j = 0; j < boxes[0].size(); j++)
                (boxes)[i][j].draw(window);
        }
        back.draw(window);
        /*****************************************************************************/
        name1.draw(window);
        name.draw(window);
        heading.draw(window);
        window.display();
        window.clear(colors[!ij]);
    }
}

int train_draw_schedule(train_business train, RenderWindow &window)
{
    Font font;
    font.loadFromFile("Font/arial.ttf");
    Text text("MANAGE TRACKS", font);

    /******************************************************************************************************/
    vector <Text_box> names;
    for(int i =0;i < 3;i++)
    {
        names.push_back(Text_box(Vector2f(10 + i*200,310),"",text.getFont()));
        names[i].setSize(Vector2f(200,30));
    }
    names[0].setText("STATION");
    names[1].setText("ARRIVAL");
    names[2].setText("DEPARTURE");
    train_schedule schedule;
    Texture texture;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    Sprite sprite(texture);
    sprite.setPosition(250, 0);
    Text_box heading(Vector2f(10, 240), "\t\t\t\t\t\t\t\t\t\t" + train.get_name() + "  SCHEDULE", &font);
    heading.setSize(Vector2f(780, 40));
    /******************************************************************************************************/
    vector<train_stop> all_stops = schedule.get_schedule(train.get_name());
    vector<vector<Button>> boxes;
    vector<string> tmpo;
    vector<Button> tmp;
    for (int i = 0; i < all_stops.size(); i++)
    {
        tmpo = all_stops[i].get_data();
        tmp.push_back(Text_box(Vector2f(10, 350 + (i * 30)), tmpo[0], text.getFont()));
        (*(tmp.end() - 1)).setSize(Vector2f(200, 30));
        tmp.push_back(Text_box(Vector2f(210, 350 + (i * 30)), tmpo[1], text.getFont()));
        (*(tmp.end() - 1)).setSize(Vector2f(200, 30));
        tmp.push_back(Text_box(Vector2f(410, 350 + (i * 30)), tmpo[2], text.getFont()));
        (*(tmp.end() - 1)).setSize(Vector2f(200, 30));
        (boxes).push_back(tmp);
        tmpo.clear();
        tmp.clear();
    }
    /*************************************************************/
    Button back(Vector2f(10, 10), "Back", *text.getFont());
    Button add(Vector2f(10, 350 + (boxes.size() * 30)), "ADD", *text.getFont());

    vector<Input_box> box;
    box.push_back(Input_box(Vector2f(210, 350 + (boxes.size() * 30)), static_cast<string>(" "), font));
    box[box.size() - 1].setSize(Vector2f(200, 30));
    box.push_back(Input_box(Vector2f(410, 350 + (boxes.size() * 30)), static_cast<string>(" "), font));
    box[box.size() - 1].setSize(Vector2f(200, 30));
    // // /***************************************************************/
    Texture texture_del, texture_done;
    texture_done.loadFromFile("Images/done.png");
    texture_del.loadFromFile("Images/delete.png");
    Sprite icon_delete(texture_del), icon_done(texture_done);
    // /******************************************************************************************************/
    View view(FloatRect(0,0,800,600));
    window.setView(view);

    int scroll_limit = all_stops.size() - 7;
    Event event;
    Vector2f pos;
    int i = 0, z = 0, y = 0, k = 0, write_cursor = 0, in1, in2, in3 = in2 = in1 = 0;
    int stop_num = 0;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                exit(0);
                break;
            case Event::MouseButtonPressed:
                pos = Vector2f(Mouse::getPosition(window));
                pos.y += ((all_stops.size() - 7) - scroll_limit)*30;
                if (write_cursor)
                {
                    write_cursor--;
                }
                for (int i = 0; i < box.size(); i++)
                    box[i].selected(false);
                if (icon_delete.getGlobalBounds().contains(pos) && stop_num)
                {
                    schedule.remove_stop(train.get_name(), stop_num);
                    return 1;
                }
                if (back.pressed(window, pos))
                {
                    return 0;
                }
                stop_num = if_pressed(boxes, window, pos);
                if (add.pressed(window, pos))
                {
                    in1=select_station(window,"Select Station");
                    k = 1;
                    icon_done.setPosition(Vector2f(611, 350 + (boxes.size() * 30)));
                }
                if (k)
                    for (int i = 0; i < box.size(); i++)
                        if (box[i].pressed(window, pos))
                        {
                            write_cursor = 1;
                            box[i].selected(true);
                        }
                if (icon_done.getGlobalBounds().contains(pos) && k)
                {
                    if (!box[1].get_input().empty() && !box[0].get_input().empty())
                    {
                        schedule.add_stop(train.get_name(), in1, box[0].get_input(), box[1].get_input());
                    }
                    return 1;
                }
                break;
                case Event::MouseWheelMoved:
                if(event.mouseWheel.delta == -1 && (scroll_limit > 0))
                {
                    scroll_limit--;
                    view.move(0,30);
                    window.setView(view);
                }
                if(event.mouseWheel.delta == 1 && (window.getDefaultView().getCenter().y - view.getCenter().y))
                {
                    scroll_limit++;
                    view.move(0,-30);
                    window.setView(view);
                }
            }
        }
        //         /*****************************************************************************/
        if (write_cursor)
        {
            for (int i = 0; i < box.size(); i++)
                if (box[i].pressed(window, pos))
                    box[i].take_input(window);
        }
        //     //     /*****************************************************************************/
        if (stop_num)
        {
            icon_delete.setPosition(Vector2f(611, (350 + ((stop_num - 1) * 30))));
            window.draw(icon_delete);
        }
        window.draw(sprite);
        switch (k)
        {
        case 0:
            add.draw(window);
            break;
        case 1:
            for (int i = 0; i < box.size(); i++)
                box[i].draw(window);
            window.draw(icon_done);
            break;
        }
        for (int i = 0; i < (boxes).size(); i++)
        {
            for (int j = 0; j < boxes[0].size(); j++)
                (boxes)[i][j].draw(window);
        }
        back.draw(window);
        for(int i =0;i < 3;i ++)
            names[i].draw(window);
        /*****************************************************************************/
        heading.draw(window);
        window.display();
        window.clear(colors[!ij]);
    }
}

void manage_schedule(RenderWindow &window)
{
    Font font;
    font.loadFromFile("Font/arial.ttf");
    Text text("MANAGE TRACKS", font);

    /******************************************************************************************************/

    Texture texture;
    texture.loadFromFile("Images/Icon"+to_string(ij)+".png");
    Sprite sprite(texture);
    sprite.setPosition(250, 0);
    Text_box heading(Vector2f(10, 240), "\t\t\t\t\t\t\t\t\t\t\tMANAGE SCHEDULE", &font);
    heading.setSize(Vector2f(780, 40));
    /******************************************************************************************************/
    train_business train;
    vector<train_business> all_train = train.all_trains();
    vector<vector<Button>> boxes;
    vector<string> tmpo;
    vector<Button> tmp;
    for (int i = 0; i < all_train.size(); i++)
    {
        tmpo = all_train[i].get_data();
        tmp.push_back(Text_box(Vector2f(10, 350 + (i * 30)), tmpo[0], text.getFont()));
        (*(tmp.end() - 1)).setSize(Vector2f(200, 30));
        tmp.push_back(Text_box(Vector2f(210, 350 + (i * 30)), tmpo[1], text.getFont()));
        (*(tmp.end() - 1)).setSize(Vector2f(200, 30));
        (boxes).push_back(tmp);
        tmpo.clear();
        tmp.clear();
    }
    /***************************************************************************/
    Texture icon_details;
    icon_details.loadFromFile("Images/details.png");
    vector<Sprite> details;
    for (int i = 0; i < all_train.size(); i++)
    {
        details.push_back(Sprite(icon_details));
        details[i].setPosition(Vector2f(410, 350 + (i * 30)));
    }
    /*************************************************************/
    Button back(Vector2f(10, 10), "Back", *text.getFont());
    /***************************************************************/
    View view(FloatRect(0,0,800,600));
    window.setView(view);

    int scroll_limit = all_train.size() - 7;
    /******************************************************************************************************/

    Event event;
    Vector2f pos;
    int i = 0, z = 0, y = 0, k = 0, write_cursor = 0, in1, in2, in3 = in2 = in1 = 0;
    int train_num = 0;
    while (window.isOpen())
    {
        if (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                exit(0);
                break;
            case Event::MouseButtonPressed:
                pos = Vector2f(Mouse::getPosition(window));
                pos.y += ((all_train.size() - 7) - scroll_limit)*30;
                if (back.pressed(window, pos))
                    return;
                for (int i = 0; i < details.size(); i++)
                    if (details[i].getGlobalBounds().contains(pos))
                        while (true)
                        {
                            if (!train_draw_schedule(all_train[i], window))
                                break;
                        }
                break;
                case Event::MouseWheelMoved:
                if(event.mouseWheel.delta == -1 && (scroll_limit > 0))
                {
                    scroll_limit--;
                    view.move(0,30);
                    window.setView(view);
                }
                if(event.mouseWheel.delta == 1 && (window.getDefaultView().getCenter().y - view.getCenter().y))
                {
                    scroll_limit++;
                    view.move(0,-30);
                    window.setView(view);
                }
                break;
            }
            window.draw(sprite);
            for (int i = 0; i < (boxes).size(); i++)
            {
                for (int j = 0; j < boxes[0].size(); j++)
                    (boxes)[i][j].draw(window);
            }
            for (int i = 0; i < details.size(); i++)
                window.draw(details[i]);
            back.draw(window);
            /*****************************************************************************/
            heading.draw(window);
            window.display();
            window.clear(colors[!ij]);
        }
    }
}
