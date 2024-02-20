# config.py


def can_build(env, platform):
    if platform == "macos":
        return False
    if env.msvc:
        print("Error: Cannot build with Steam Audio MSVC.")
        return False
    return True


def configure(env):
    pass
