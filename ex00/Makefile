NAME = btc
SRCS = BitcoinExchange.cpp main.cpp
OBJS = $(SRCS:%.cpp=%.o)
CXX = c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror -pedantic

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean

