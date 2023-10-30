#include <lts/language.h>

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif

#include <lts/util.h>

void LTS_push_language(lua_State *L, TSLanguage *target) {
	TSLanguage **ud = lua_newuserdata(L, sizeof *ud);
	*ud = target;
	LTS_util_set_metatable(L, LTS_LANGUAGE_METATABLE_NAME);
}

TSLanguage **LTS_check_language(lua_State *L, int idx) {
	return luaL_checkudata(L, idx, LTS_LANGUAGE_METATABLE_NAME);
}

#define SYM_PREFIX "tree_sitter_"
#define SYM_PREFIX_LEN (sizeof SYM_PREFIX - 1)

static TSLanguage *load(
	lua_State *L,
	luaL_Buffer *err_buf,
	const char *path,
	const char *name,
	size_t name_len
) {
#ifdef _WIN32
	HMODULE dl = LoadLibrary(path);
#else
	void *dl = dlopen(path, RTLD_NOW | RTLD_LOCAL);
#endif
	if (!dl) {
#ifdef _WIN32
		lua_pushfstring(L,
			"\n\tcould not load dynamic library: error code %d",
			GetLastError()
		);
#else
		lua_pushfstring(L, "\n\tcould not load dynamic library: %s", dlerror());
#endif
		luaL_addvalue(err_buf);
		return NULL;
	}

	size_t sym_len = SYM_PREFIX_LEN + name_len;
	char *sym = malloc(sym_len + 1);
	sym[sym_len] = '\0';

	memcpy(sym, SYM_PREFIX, SYM_PREFIX_LEN);
	memcpy(sym + SYM_PREFIX_LEN, name, name_len);

#ifdef _WIN32
	TSLanguage *(*lang_func)(void) =
		(TSLanguage *(*)(void)) (void (*)(void)) GetProcAddress(dl, sym);
#else
	TSLanguage *(*lang_func)(void);
	*((void **) &lang_func) = dlsym(dl, sym);
#endif
	free(sym);
	if (!lang_func) {
#ifdef _WIN32
		FreeLibrary(dl);
		lua_pushfstring(L,
			"\n\tcould not load symbol from dynamic library: error code %d",
			GetLastError()
		);
#else
		dlclose(dl);
		lua_pushfstring(L, "\n\tcould not load symbol from dynamic library: %s", dlerror());
#endif
		luaL_addvalue(err_buf);
		return NULL;
	}

	return lang_func();
}

#undef SYM_PREFIX
#undef SYM_PREFIX_LEN

static int LTS_language_load(lua_State *L) {
	const char *path = luaL_checkstring(L, 1);
	size_t name_len;
	const char *name = luaL_checklstring(L, 2, &name_len);

	luaL_Buffer err_buf;
	luaL_buffinit(L, &err_buf);
	lua_pushfstring(L, 
		"could not require language '%s' from '%s'\nreason:",
		name, path
	);
	luaL_addvalue(&err_buf);

	TSLanguage *lang = load(L, &err_buf, path, name, name_len);
	if (lang) {
		LTS_push_language(L, lang);
		return 1;
	}

	luaL_pushresult(&err_buf);
	return lua_error(L);
}

static int LTS_language_require(lua_State *L) {
	size_t name_len;
	const char *name = luaL_checklstring(L, 1, &name_len);
	size_t cpath_len;
	const char *cpath = luaL_optlstring(L, 2, NULL, &cpath_len);

	if (!cpath) {
		lua_settop(L, 1);
		lua_getglobal(L, "package");
		lua_getfield(L, 2, "cpath");
		cpath = luaL_checklstring(L, 3, &cpath_len);
	}

	luaL_Buffer err_buf;
	luaL_buffinit(L, &err_buf);
	lua_pushfstring(L, "could not require language '%s'\nreason:", name);
	luaL_addvalue(&err_buf);

	size_t start = 0;
	for (size_t i = 0; i <= cpath_len; i++) {
		if (cpath[i] == ';' || i == cpath_len) {
			if (start == i) goto next;

			size_t q_count = 0;
			for (size_t j = start; j < i; j++) {
				if (cpath[j] == '?') q_count++;
			}

			size_t path_len = i - start + name_len * q_count - q_count;
			char *path = malloc((path_len + 1) * sizeof *path);
			path[path_len] = '\0';

			size_t written = 0;
			for (size_t j = start; j < i; j++) {
				if (cpath[j] == '?') {
					memcpy(path + written, name, name_len);
					written += name_len;
				} else {
					path[written] = cpath[j];
					written++;
				}
			}

			TSLanguage *lang = load(L, &err_buf, path, name, name_len);
			free(path);
			if (lang) {
				LTS_push_language(L, lang);
				return 1;
			}

		next:
			start = i + 1;
		}
	}

	luaL_pushresult(&err_buf);
	return lua_error(L);
}

static int LTS_language_version(lua_State *L) {
	TSLanguage *self = *LTS_check_language(L, 1);

	lua_pushinteger(L, ts_language_version(self));
	return 1;
}

static int LTS_language_eq(lua_State *L) {
	TSLanguage *self = *LTS_check_language(L, 1);
	TSLanguage *other = *LTS_check_language(L, 2);

	lua_pushboolean(L, self == other);
	return 1;
}

static const luaL_Reg methods[] = {
	{ "version", LTS_language_version },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__eq", LTS_language_eq },
	{ NULL, NULL }
};

static const luaL_Reg funcs[] = {
	{ "load", LTS_language_load },
	{ "require", LTS_language_require },
	{ NULL, NULL }
};

void LTS_setup_language(lua_State *L) {
	LTS_util_make_metatable(L, LTS_LANGUAGE_METATABLE_NAME, methods, metamethods);
	LTS_util_make_functable(L, LTS_LANGUAGE_FUNCTABLE_NAME, funcs);
}
