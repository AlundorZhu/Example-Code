CXXFLAGES=-Wall -Werror -std=c++11
CXX=g++

All: test_pqueue test_bstream unzap zap

test_pqueue: test_pqueue.cc
	$(CXX) $(CXXFLAGES) -g -o $@ $^ -pthread -lgtest

test_bstream: test_bstream.cc
	$(CXX) $(CXXFLAGES) -g -o $@ $^ -pthread -lgtest

zap: zap.cc
	$(CXX) $(CXXFLAGES) -o $@ $^

unzap: unzap.cc
	$(CXX) $(CXXFLAGES) -o $@ $^

clean:
	rm -f unzap zap test_pqueue test_bstream
