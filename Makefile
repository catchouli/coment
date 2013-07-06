all:
	@mkdir -p bin
	$(MAKE) -C Coment
	$(MAKE) -C Sample

clean:
	@rm -rf bin
	$(MAKE) clean -C Coment
	$(MAKE) clean -C Sample

.PHONY: all clean
