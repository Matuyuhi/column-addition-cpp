run:
	rm -rf build
	mkdir -p build
	cd build && cmake .. && make
	./build/work

docker:
	docker compose up --build