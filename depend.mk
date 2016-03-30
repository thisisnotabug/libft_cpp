INCLUDE_FLAGS += -I$(O_DIR)/_public
OBJ_DIR_TREE += $(O_DIR)/ft/ $(O_DIR)/_public/ft/templates/ \
	$(O_DIR)/_public/ft/ $(O_DIR)/_public/ $(O_DIR)/
O_FILES += $(O_DIR)/ft/assert.o $(O_DIR)/ft/padformat.o
PUBLIC_LINKS += $(O_DIR)/_public/ft/assert.hpp $(O_DIR)/_public/ft/Color.hpp \
	$(O_DIR)/_public/ft/padformat.hpp $(O_DIR)/_public/ft/Rect.hpp \
	$(O_DIR)/_public/ft/TupleRef.hpp $(O_DIR)/_public/ft/type_traits.hpp \
	$(O_DIR)/_public/ft/utils.hpp $(O_DIR)/_public/ft/Vec.hpp \
	$(O_DIR)/_public/ft/templates/Rect.tpp \
	$(O_DIR)/_public/ft/templates/Vec2.tpp \
	$(O_DIR)/_public/ft/templates/Vec3.tpp \
	$(O_DIR)/_public/ft/templates/Vec4.tpp

# module ft::ft
$(O_DIR)/ft/assert.o: ft/assert.cpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp
$(O_DIR)/ft/padformat.o: ft/padformat.cpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp

# public links
$(O_DIR)/_public/ft/Color.hpp: ft/public/Color.hpp
$(O_DIR)/_public/ft/Rect.hpp: ft/public/Rect.hpp
$(O_DIR)/_public/ft/TupleRef.hpp: ft/public/TupleRef.hpp
$(O_DIR)/_public/ft/Vec.hpp: ft/public/Vec.hpp
$(O_DIR)/_public/ft/assert.hpp: ft/public/assert.hpp
$(O_DIR)/_public/ft/padformat.hpp: ft/public/padformat.hpp
$(O_DIR)/_public/ft/templates/Rect.tpp: ft/public/templates/Rect.tpp
$(O_DIR)/_public/ft/templates/Vec2.tpp: ft/public/templates/Vec2.tpp
$(O_DIR)/_public/ft/templates/Vec3.tpp: ft/public/templates/Vec3.tpp
$(O_DIR)/_public/ft/templates/Vec4.tpp: ft/public/templates/Vec4.tpp
$(O_DIR)/_public/ft/type_traits.hpp: ft/public/type_traits.hpp
$(O_DIR)/_public/ft/utils.hpp: ft/public/utils.hpp
