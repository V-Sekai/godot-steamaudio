# config.py


def can_build(env, platform):
    if platform in ["web", "android", "macos"]:
        return False
    if env.msvc:
        print("Error: Cannot build with Steam Audio MSVC.")
        return False
    return True


def configure(env):
    pass
